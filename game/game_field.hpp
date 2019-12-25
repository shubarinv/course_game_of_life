//
// Created by vhundef on 25.12.2019.
//

#ifndef PROGONHLANG_GAME_FIELD_HPP
#define PROGONHLANG_GAME_FIELD_HPP


#include <SDL_rect.h>
#include <SDL_log.h>
#include <stdexcept>
#include "cell.hpp"
#include <vector>

using namespace std;
class GameField {
	SDL_Window *window;
public:
	std::vector<std::vector<Cell*>> cells;
	explicit GameField(SDL_Window *game_window) {
		window = game_window;

		if(window==nullptr){
			std::string error = SDL_GetError();
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "GameField->constructor: Window is null");
			throw std::runtime_error("GameField->constructor: Window is null");
		}

		int h,w;
		SDL_GetWindowSize(window, &w,&h);
		for (int i = 0; i < w / 16; ++i) {
			for (int j = 0; j < h / 16; ++j) {
				/*Cell* tmp=new Cell(window);
				cells[i].push_back(tmp);
				cells[i][j]->setLocation(i,j);*/
			}
		}
	}

	void drawBoard() {
		if (cells.empty()) {
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "GameField->drawBoard: Cells array is empty");
			//throw std::runtime_error("GameField->drawBoard: Cells array is NULL");
		}

		int h,w;
		SDL_GetWindowSize(window, &w,&h);

		for (int i = 0; i < w / 16; ++i) {
			for (int j = 0; j < h / 16; ++j) {
			//	cells[i][j]->redraw();
			}
		}

	}
};


#endif //PROGONHLANG_GAME_FIELD_HPP
