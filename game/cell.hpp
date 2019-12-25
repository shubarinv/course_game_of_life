#include <SDL_rect.h>
#include <SDL_surface.h>
#include <string>
#include <SDL_log.h>
#include <stdexcept>
#include <SDL_video.h>

class Cell {
private:
	SDL_Rect block{};
	SDL_Surface *surface{};
	SDL_Window *window;

public:
	char status = 'd'; ///< a-alive d-dead b-born
	explicit Cell(SDL_Window *game_window) {
		block.h = 16;
		block.w = block.h;
		window = game_window;
		surface=SDL_GetWindowSurface(window);
	}

	void redraw() {
		if(surface== nullptr){
			std::string error = SDL_GetError();

			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Cell->redraw: Surface is null... what am i supposed to draw on?\n%s", error.c_str());
			throw std::runtime_error("Cell->redraw: Surface is null");
		}
		switch (status) {
			case 'd':
				SDL_FillRect(surface, &block, 0x404443);
				break;
			case 'a':
				SDL_FillRect(surface, &block, 0x6FAB63);
				break;
				//case 'b':SDL_FillRect(surface, &block, 0x8D3516);break;

		}
	}

	void setLocation(int x, int y) {
		int h,w;
		SDL_GetWindowSize(window, &w,&h);
		if (x * block.h <= w && x * block.h >= 0 &&
		    y * block.h <= h &&
		    y * block.h >= 0) {
			block.x = x * block.h;
			block.y = y * block.h;
		} else {
			std::string error = "Cell->SetLocationFailed new coords are out of bounds";
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
			throw std::runtime_error("Cell->SetLocationFailed new coords are out of bounds");
		}
	}
};