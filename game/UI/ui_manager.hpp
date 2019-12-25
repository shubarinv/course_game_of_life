//
// Created by vhundef on 24.12.2019.
//

#ifndef PROGONHLANG_UI_MANAGER_HPP
#define PROGONHLANG_UI_MANAGER_HPP


#include <SDL_ttf.h>
#include <iostream>

class UI_Manager {
	TTF_Font *font{};
	SDL_Renderer *renderer;
	int fontSize = {};
	std::string fontName = "Roboto-Medium";
public:
	UI_Manager(SDL_Surface *pSurface, SDL_Renderer *pRenderer) {
		if (TTF_Init() == -1) {
			std::string error = TTF_GetError();
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
			throw std::runtime_error("UI_Manager->TTF_OpenFont: Attempt to open font was unsuccessful");
		}

		font = TTF_OpenFont((fontName + ".ttf").c_str(), 16);
		if (!font) {
			std::string error = TTF_GetError();
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
			throw std::runtime_error("UI_Manager->TTF_OpenFont: Attempt to open font was unsuccessful");
		}
		renderer = pRenderer;
	}

	void changeFontSize(int size) {
		font = TTF_OpenFont((fontName + ".ttf").c_str(), size);
		if (!font) {
			std::string error = TTF_GetError();
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
			throw std::runtime_error("UI_Manager->changeFontSize: Attempt to change font size was unsuccessful");
		}
		fontSize = size;
	}

	void printText(const std::string &text, int x, int y, SDL_Color color = {0, 0, 0},
	               int font_size = 16) {
		changeFontSize(font_size);
		SDL_Surface *surfaceMessage = TTF_RenderUTF8_Solid(font, text.c_str(),
		                                                   color); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
		SDL_Texture *Message = SDL_CreateTextureFromSurface(renderer,
		                                                    surfaceMessage); //now you can convert it into a texture
		SDL_Rect Message_rect; //create a rect
		Message_rect.x = x;  //controls the rect's x coordinate
		Message_rect.y = y; // controls the rect's y coordinte
		TTF_SizeUTF8(font, text.c_str(), &Message_rect.w, &Message_rect.h);
		SDL_RenderCopy(renderer, Message, nullptr,
		               &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

	}
};


#endif //PROGONHLANG_UI_MANAGER_HPP
