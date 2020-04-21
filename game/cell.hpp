#include <SDL_log.h>
#include <SDL_rect.h>
#include <SDL_surface.h>
#include <SDL_video.h>

#include <stdexcept>
#include <string>

class Cell {
  struct twoInt {
	int a, b;
  };

 private:
  SDL_Rect block{};///@brief Тело клетки
  int aliveFor{0}; /// сколько тиков жива клетка
  char state = 'd';///< a-alive d-dead b-born h-hover

 public:
  void setState(char _state) {/// позволяет задать состояние клетке
	Cell::state = _state;
  }

  /**
   * @brief позволяет получить состояние клетки
   * @returns если клетка не мертва, не имеет неопределённое состояние и на неё не наведен курсор в режиме редактирования, то клетка считается живой
   * иначе клетка считается мёртвой**/
  char getState() const {
	if (state != 'd' && state != 'u' && state != 'h') return 'a';
	else
	  return state;
  }

  char next_state = '-'; ///< a-alive d-dead b-born h-hover
  char deathReason = 'u';// l= not enough neighbours; u= unset; c=to much cells nearby
  Cell() {
	block.h = 16;
	block.w = block.h;
  }

  /// @brief Перерисовавыет клетку цветом который соответствует её состоянию
  void redraw(SDL_Renderer* renderer) {
	SDL_RenderDrawRect(renderer, &block);
	switch (state) {
	  case 'd':///< клетка мертва
		SDL_SetRenderDrawColor(renderer, 64, 68, 67, 255);
		aliveFor = 0;
		break;
	  case 'h':///< Над клеткой находится курсор(в режиме редактирования)
		SDL_SetRenderDrawColor(renderer, 224, 187, 0, 255);
		break;
	  case 'b':///< Клетка только была создана
		SDL_SetRenderDrawColor(renderer, 4, 141, 204, 255);
		aliveFor++;
		state = 'a';
		break;
	}
	if (state == 'a') {                     ///< клетка жива
											// чем больше живет клетка, тем темнее она будет
	  if (aliveFor >= 0 && aliveFor <= 20) {///До 20 тиков включительно
		SDL_SetRenderDrawColor(renderer, 14, 255, 0, 255);
	  } else if (aliveFor > 20 && aliveFor <= 40)///До 40 тиков включительно
		SDL_SetRenderDrawColor(renderer, 8, 144, 0, 255);
	  else if (aliveFor > 40 && aliveFor <= 60)///До 60 тиков включительно
		SDL_SetRenderDrawColor(renderer, 10, 93, 0, 255);
	  else if (aliveFor > 60 && aliveFor <= 80)///До 80 тиков включительно
		SDL_SetRenderDrawColor(renderer, 7, 70, 0, 255);
	  else if (aliveFor > 80)///от 80 тиков
		SDL_SetRenderDrawColor(renderer, 6, 59, 0, 255);
	  aliveFor++;
	}
	// Рисует клетку
	SDL_RenderFillRect(renderer, &block);
  }

  /**@brief Задаёт положение клетке
	 * @param x: координата верхнего левого угла клетки по оси x
	 * @param y: координата верхнего левого угла клетки по оси y
	 * @param window: Указатель на окно размером которого будет ограгниченна максимальная координата
	 **/
  void setLocation(int x, int y, SDL_Window* window) {
	int h, w;
	SDL_GetWindowSize(window, &w, &h);
	if (x * block.h <= w && x * block.h >= 0 && y * block.h <= h && y * block.h >= 0) {
	  block.x = x * block.h;
	  block.y = y * block.h;
	} else {
	  std::string error = "ОШИБКА: Cell->SetLocation новые координаты клетки выходят за границы экрана X:" + std::to_string(x) + " Y:" + std::to_string(y * block.h) + " в то время как максимально возможные значкения: " + std::to_string(w) + "x" + std::to_string(h);
	  SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
	  throw std::runtime_error(error);
	}
  }

  /**
	 * @brief Находит "относительное"(по отношению к другим клеткам) положение клетки
	 * @param Y координата верхнего левого угла клетки по оси Y
	 * @param X координата верхнего левого угла клетки по оси X
	 * @returns Возвращает "относительное"(по отношению к другим клеткам) положение клетки например (2,3) - 2 по оси Y,3 по оси X
	 * **/
  static twoInt getRelativeLocation(int y, int x) {
	return {x / 16, y / 16};
  }

  ///@brief Применяет новое состояние к клетке
  void applyNewState() {
	if (next_state != '-') state = next_state;
	next_state = '-';
  }
};