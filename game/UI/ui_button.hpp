//
// Created by vhundef on 27.12.2019.
//

#ifndef PROGONHLANG_UI_BUTTON_HPP
#define PROGONHLANG_UI_BUTTON_HPP

#include <SDL_rect.h>

#include <string>

#include "ui_manager.hpp"

class uiButton {
 private:
  SDL_Rect body{};                      ///< тело кнопки
  SDL_Color defaultColor{127, 179, 114};///< Стандартный цвет кнопки
  SDL_Color hoverColor{89, 150, 74};    ///< Цвет при наведении курсора на кнопку
  SDL_Color disabledColor{82, 82, 82};  ///< Цвет выключенной кнопки
  ScreenManager *uiManager{};
  std::string text = "UNSET";
  int textPosX{};    ///< Позиция текста по оси X
  int textPosY{};    ///< Позиция текста по оси Y
  bool enabled{true};///< хранит данные о том включена кнопка или нет
  bool hover{false}; ///< Хранит данные о том находится ли курсор над кнопкой
  int fontSize{20};  ///< размер шрифта

 public:
  /**
   * @brief Конструктор класса Button
   * @param string Текст внутри кнопки
   * @param _uiManager Указатель на менеджер экрана
   * @param x положение кнопки по оси X
   * @param y Позиция текста по оси Y
   * @param width Ширина кнопки
   * @param height Высота кнопки
   * @param _fontSize размер шрифта
   */
  uiButton(const std::string &string, ScreenManager *_uiManager, int x, int y, int width, int height, int _fontSize = 20) {
	if (_uiManager == nullptr) {
	  std::string error = "UIButton->Constructor->uiManager is null";
	  SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
	  throw std::runtime_error("Unable to button uiManager is null");
	}
	uiManager = _uiManager;
	body.x = x;
	body.y = y;
	body.w = width;
	body.h = height;
	fontSize = _fontSize;
	text = string;
	centerText();
  }

  ///@brief Возвращает включена ли кнопка
  [[nodiscard]] bool isEnabled() const {
	return enabled;
  }

  ///@brief Позволяет включить/выключить кнопку
  void setEnabled(bool _enabled) {
	uiButton::enabled = _enabled;
  }

  ///@brief Возвращает нахидится ли курсор над кнопкой
  [[nodiscard]] bool isHover() const {
	return hover;
  }

  /** @brief проверяет нахидится ли что-то в пределах кнопки
 *
 * @param x положение по оси
 * @param y положение по оси
 * @return true - если кординаты находятся в пределах кнопки иначе False
 */
  bool collisionCheck(int x, int y) {
	return x >= body.x && x <= body.x + body.w && y >= body.y && y <= body.y + body.h;
  }

  ///@brief ставит текст по центру кнопки
  void centerText() {
	int textWidth = uiManager->getTextSize(text, fontSize).a;
	int textHeight = uiManager->getTextSize(text, fontSize).b;
	textPosX = (body.x + body.w / 2) - textWidth / 2;
	textPosY = (body.y + body.h / 2) - textHeight / 2;
  }
  /**
 * @brief Рисует кнопку
 * @param x координата мыши по оси X
 * @param y координаты мыши по оси Y
   * Координаты используются в функции проверки того находитяся ли мышь в пределах кнопки
 */
  void draw(int x, int y) {
	SDL_RenderDrawRect(uiManager->getRenderer(), &body);
	hover = collisionCheck(x, y);
	if (enabled) {
	  if (hover) {
		SDL_SetRenderDrawColor(uiManager->getRenderer(), hoverColor.r, hoverColor.g, hoverColor.b, 255);
		SDL_FillRect(SDL_GetWindowSurface(uiManager->getWindow()), &body, ScreenManager::rgbToHex(hoverColor));
	  } else {
		SDL_SetRenderDrawColor(uiManager->getRenderer(), defaultColor.r, defaultColor.g, defaultColor.b, 255);
		SDL_FillRect(SDL_GetWindowSurface(uiManager->getWindow()), &body, ScreenManager::rgbToHex(defaultColor));
	  }
	} else {
	  SDL_SetRenderDrawColor(uiManager->getRenderer(), disabledColor.r, disabledColor.g, disabledColor.b, 255);
	  SDL_FillRect(SDL_GetWindowSurface(uiManager->getWindow()), &body, ScreenManager::rgbToHex(disabledColor));
	}
	// Render rect
	SDL_RenderFillRect(uiManager->getRenderer(), &body);
	uiManager->printText(text, textPosX, textPosY, {255, 255, 255}, fontSize);
  }
  ///@brief позволяет задать стандартный цвет кнопки
  void setDefaultColor(const SDL_Color &_defaultColor) {
	uiButton::defaultColor = _defaultColor;
  }
  ///@brief позволяет задать цвет при наведении курсора на кнопку
  void setHoverColor(const SDL_Color &_hoverColor) {
	uiButton::hoverColor = _hoverColor;
  }
  ///@brief позволяет задать цвет выключенной кнопки
  void setDisabledColor(const SDL_Color &_disabledColor) {
	uiButton::disabledColor = _disabledColor;
  }
};

#endif//PROGONHLANG_UI_BUTTON_HPP
