//
// Created by vhundef on 25.12.2019.
//

#ifndef PROGONHLANG_GAME_FIELD_HPP
#define PROGONHLANG_GAME_FIELD_HPP


#include <SDL_rect.h>
#include <SDL_log.h>
#include <stdexcept>

class GameField {
	bool **cells{};
	int fieldSizeX{};
	int fieldSizeY{};

public:
	GameField() {

	}

	void drawBoard() {
		if (cells == nullptr) {
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Cells array is empty");
			throw std::runtime_error("GameField->drawBoard: Cells array is NULL");
		}

	}
};


#endif //PROGONHLANG_GAME_FIELD_HPP
