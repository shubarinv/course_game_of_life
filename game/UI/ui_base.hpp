//
// Created by vhundef on 24.12.2019.
//

#ifndef PROGONHLANG_UI_BASE_HPP
#define PROGONHLANG_UI_BASE_HPP


#include <string>
#include <SDL_rect.h>
#include <SDL_surface.h>
#include "ui_manager.hpp"

class UI_Base {
public:
	UI_Base(UI_Manager *ui_Manager, SDL_Window *window) {
		uiManager = ui_Manager;
		win = window;
	}


protected:
	UI_Manager *uiManager{};
	SDL_Window *win{};
	/// TODO: Remove this function, add button class.
	[[deprecated]]void createButton(int x, int y, int width, int height, const std::string &text, int btnColor,
	                                SDL_Color textColor) {///< @deprecated due to complexity @bug incorrect alignment is cyrillic symbols are used
		SDL_Rect button;
		button.x = x;
		button.y = y;
		button.w = width;
		button.h = height;
		SDL_FillRect(SDL_GetWindowSurface(win), &button, btnColor);

		uiManager->printText(text, (x + width / 2) - uiManager->getFontSize() / 2 * (text.length() / 2.0),
		                     (y + height / 2) - uiManager->getFontSize() / 2,
		                     textColor, 20);
	}
};


#endif //PROGONHLANG_UI_BASE_HPP
