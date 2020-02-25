//
// Created by vhundef on 25.12.2019.
//

#ifndef PROGONHLANG_GAME_FIELD_HPP
#define PROGONHLANG_GAME_FIELD_HPP

#include <SDL_log.h>
#include <SDL_rect.h>
#include <time.h>

#include <ctime>
#include <fstream>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>

#include "cell.hpp"

using namespace std;

class GameField {
 private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  int aliveCells = 0;

 public:
  [[nodiscard]] int getAliveCells() const {
	return aliveCells;
  }

 public:
  std::vector<std::vector<Cell>> cells;

  explicit GameField(SDL_Window *game_window, SDL_Renderer *_renderer) {
	window = game_window;

	if (window == nullptr) {
	  std::string error = SDL_GetError();
	  SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "GameField->constructor: Window is null");
	  throw std::runtime_error("GameField->constructor: Window is null");
	}
	if (_renderer == nullptr) {
	  std::string error = SDL_GetError();
	  SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "GameField->constructor: _renderer is null");
	  throw std::runtime_error("GameField->constructor: _renderer is null");
	}
	renderer = _renderer;
	int h, w;
	SDL_GetWindowSize(window, &w, &h);

	for (int i = 0; i <= w / 16; ++i) {
	  vector<Cell> row;
	  for (int j = 0; j <= h / 16; j++) {
		row.emplace_back(window, renderer);
		row.back().setLocation(i, j);
	  }
	  cells.push_back(row);
	}
	randomiseField();
  }
  void randomiseField() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 10000);
	for (auto &row : cells) {
	  for (auto &cell : row) {
		unsigned int num = dis(gen);
		if (num % 5 != 0) {
		  cell.setState('u');
		} else {
		  cell.setState('a');
		}
	  }
	}
  }
  void clearBoard() {
	for (auto &cell : cells) {
	  for (int j = 0; j < cells[0].size(); j++) {
		cell[j].setState('d');
	  }
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

  /// @brief checking compliance with rules
  void checkForNeighbors() {
	int neighbors = 0;
	aliveCells = countAliveCells();
	for (int i = 0; i < cells.size(); ++i) {
	  for (int j = 0; j < cells[0].size(); ++j) {
		if (getElement(i, j - 1)->getState() == 'a') neighbors++;    //checking cell on the left
		if (getElement(i, j + 1)->getState() == 'a') neighbors++;    //checking cell on the right
		if (getElement(i - 1, j)->getState() == 'a') neighbors++;    //checking cell on the top
		if (getElement(i + 1, j)->getState() == 'a') neighbors++;    //checking cell on the bottom
		if (getElement(i - 1, j - 1)->getState() == 'a') neighbors++;//checking cell on the top left
		if (getElement(i - 1, j + 1)->getState() == 'a') neighbors++;//checking cell on the top right
		if (getElement(i + 1, j - 1)->getState() == 'a') neighbors++;//checking cell on the bottom left
		if (getElement(i + 1, j + 1)->getState() == 'a') neighbors++;//checking cell on the bottom right
		if (neighbors < 2) {
		  cells[i][j].next_state = 'd';
		  cells[i][j].deathReason = 'l';
		} else if (neighbors > 3) {
		  cells[i][j].next_state = 'd';
		  cells[i][j].deathReason = 'c';
		} else if (neighbors == 3) {
		  cells[i][j].next_state = 'b';
		  cells[i][j].deathReason = 'u';
		}
		neighbors = 0;
	  }
	}
	for (auto &cell : cells) {
	  for (int j = 0; j < cells[0].size(); ++j) {
		cell[j].applyNewState();
	  }
	}
  }

  int countAliveCells() {
	int _aliveCells = 0;
	for (int i = 0; i < cells.size(); ++i) {
	  for (int j = 0; j < cells[0].size(); ++j) {
		if (getElement(i, j)->getState() == 'a') _aliveCells++;
	  }
	}
	return _aliveCells;
  }

  Cell *getElement(int column, int row) {
	if (column < 0)
	  column = cells.size() - 1;
	if (column == cells.size())
	  column = 0;
	if (row < 0)
	  row = cells[column].size() - 1;
	if (row == cells[column].size())
	  row = 0;
	return &cells[column][row];
  }

  std::vector<std::vector<Cell>> getField() {
	return cells;
  }

  void setField(std::vector<std::vector<Cell>> field) {
	cells = std::move(field);
  }
};

#endif//PROGONHLANG_GAME_FIELD_HPP
