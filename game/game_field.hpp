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
#include <random>

using namespace std;

class GameField {
	SDL_Window *window;
public:
	std::vector<std::vector<Cell>> cells;

	explicit GameField(SDL_Window *game_window) {
		window = game_window;

		if (window == nullptr) {
			std::string error = SDL_GetError();
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "GameField->constructor: Window is null");
			throw std::runtime_error("GameField->constructor: Window is null");
		}

		int h, w;
		SDL_GetWindowSize(window, &w, &h);
		/*for (int i = 0; getline(in, line); i++) {
			vector<int> row; //создаем одномерный вектор
			for (int j = 0; j < line.size(); j++) {
				row.push_back(line[j]); //набиваем значениями
			}
			matrix.push_back(row); запихиваем полученный одномерный вектор в двумерный.
		};*/
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(1, 10000);

		for (int i = 0; i <= w / 16; ++i) {
			vector<Cell> row;
			for (int j = 0; j <= h / 16; j++) {
				row.emplace_back(window);
				row.back().setLocation(i, j);
				unsigned int num = dis(gen);
				if (num % 2 == 0) {
					row.back().state = 'u';
				} else {
					row.back().state = 'a';
				}
			}
			cells.push_back(row);
		}
	}

	void drawBoard() {
		if (cells.empty()) {
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "GameField->drawBoard: Cells array is empty");
			//throw std::runtime_error("GameField->drawBoard: Cells array is NULL");
		}

		int h, w;
		SDL_GetWindowSize(window, &w, &h);

		for (int i = 0; i < w / 16; ++i) {
			for (int j = 0; j < h / 16; ++j) {
				cells[i][j].redraw();
			}
		}

	}

	void checkForNeibourghs() {
		int neibourghs = 0;
		for (int i = 0; i < cells.size(); ++i) {
			for (int j = 0; j < cells[0].size(); ++j) {
				if (getElement(i, j - 1)->state == 'a')neibourghs++; //checking cell on the left
				if (getElement(i, j + 1)->state == 'a')neibourghs++; //checking cell on the right
				if (getElement(i - 1, j)->state == 'a')neibourghs++; //checking cell on the top
				if (getElement(i + 1, j)->state == 'a')neibourghs++; //checking cell on the bottom
				if (getElement(i - 1, j - 1)->state == 'a')neibourghs++; //checking cell on the top left
				if (getElement(i - 1, j + 1)->state == 'a')neibourghs++; //checking cell on the top right
				if (getElement(i + 1, j - 1)->state == 'a')neibourghs++; //checking cell on the bottom left
				if (getElement(i + 1, j + 1)->state == 'a')neibourghs++; //checking cell on the bottom right
				if (neibourghs < 2) {
					cells[i][j].next_state = 'd';
					cells[i][j].deathReason = 'l';
				} else if (neibourghs > 3) {
					cells[i][j].next_state = 'd';
					cells[i][j].deathReason = 'c';
				} else if (neibourghs == 3) {
					cells[i][j].next_state = 'a';
					cells[i][j].deathReason = 'u';
				}
				neibourghs = 0;
			}
		}
		for (auto & cell : cells) {
			for (int j = 0; j < cells[0].size(); ++j) {
				cell[j].applyNewState();
			}
		}

	}

	Cell *getElement(int column, int row) {
		//cout<<"Got "<<column<<" "<<row<<endl;
		if (column < 0)
			column = cells.size() - 1;
		if (column == cells.size())
			column = 0;
		if (row < 0)
			row = cells[column].size() - 1;
		if (row == cells[column].size())
			row = 0;
		//cout<<"Interpreted as "<<column<<" "<<row<<endl;
		return &cells[column][row];
	}
};


#endif //PROGONHLANG_GAME_FIELD_HPP
