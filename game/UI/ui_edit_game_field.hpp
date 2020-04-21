//
// Created by vhundef on 02.01.2020.
//

#ifndef PROGONHLANG_UI_EDIT_GAME_FIELD_HPP
#define PROGONHLANG_UI_EDIT_GAME_FIELD_HPP

#include "../game_field.hpp"
#include "ui_base.hpp"

class uiEditGameField : private virtual UI_Base {
 private:
  GameField *gameField;
  Cell *prevCell = nullptr;
  char startingState = ' ';

 public:
  uiEditGameField(ScreenManager *_screenManager, GameField *_gameField) {
	if (_screenManager == nullptr) {
	  throw runtime_error("ERROR: UIEditGameField(ScreenManager*,GameField*) ScreenManager is NULL");
	}
	screenManager = _screenManager;
	gameField = _gameField;
  }

  void show() {
	screenManager->printText("EDIT", screenManager->getWindowResolutionX() / 2 - screenManager->getTextSize("EDIT", 30).a, screenManager->getTextSize("EDIT", 30).b / 2, {255, 255, 255}, 30);
	Cell *tmp = gameField->getElement(Cell::getRelativeLocation(screenManager->getInputManager()->getMouseCoords().x, screenManager->getInputManager()->getMouseCoords().y));
	if (prevCell != tmp && prevCell != nullptr) {
	  prevCell->applyNewState();
	  startingState = tmp->getState();
	  tmp->setState('h');
	  tmp->next_state = startingState;
	}
	if (screenManager->getInputManager()->getMouseState() & SDL_BUTTON_LMASK) {
	  if (tmp->next_state == 'a') {
		tmp->setState('d');
		tmp->next_state = '-';
	  }
	  if (tmp->next_state == 'd') {
		tmp->setState('b');
		tmp->next_state = '-';
	  }
	}
	prevCell = tmp;
  }
};

#endif//PROGONHLANG_UI_EDIT_GAME_FIELD_HPP
