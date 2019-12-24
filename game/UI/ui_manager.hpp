//
// Created by vhundef on 24.12.2019.
//

#ifndef PROGONHLANG_UI_MANAGER_HPP
#define PROGONHLANG_UI_MANAGER_HPP


#include <SDL_ttf.h>
#include <iostream>

class UI_Manager {
	TTF_Font *font{};
	SDL_Surface *textSurface{};
	std::string fontName = "";
public:
	UI_Manager() {
		font = TTF_OpenFont((fontName + ".ttf").c_str(), 16);
		if (!font) {
			std::string error = TTF_GetError();
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
			throw std::runtime_error("Attempt to open font was unsuccessful");
		}
	}

	void printText(const std::string &text, int x, int y, SDL_Color color = {0, 0, 0}) {
		SDL_Surface *text_surface;
		if (!(text_surface = TTF_RenderUTF8_Solid(font, text.c_str(), color))) {
			std::string error = TTF_GetError();
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
		} else {
			SDL_BlitSurface(text_surface, nullptr, text_surface, nullptr);
			//perhaps we can reuse it, but I assume not for simplicity.
			SDL_FreeSurface(text_surface);
		}
	}
};


#endif //PROGONHLANG_UI_MANAGER_HPP
