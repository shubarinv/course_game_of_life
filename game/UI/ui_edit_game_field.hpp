//
// Created by vhundef on 02.01.2020.
//

#ifndef PROGONHLANG_UI_EDIT_GAME_FIELD_HPP
#define PROGONHLANG_UI_EDIT_GAME_FIELD_HPP


#include "ui_base.hpp"
#include "../game_field.hpp"

class uiEditGameField : private virtual UI_Base {
private:
    GameField *gameField;
    Cell *prevCell = nullptr;
    char startingState = ' ';
public:
    uiEditGameField(UI_Manager *ui_Manager, SDL_Window *window, std::string _locale, GameField *_gameField) : UI_Base(
            ui_Manager, window,
            std::move(_locale)) {
        gameField = _gameField;
    }

    void show() {
        uiManager->printText("EDIT", uiManager->getWindowResolutionX() / 2 - uiManager->getTextSize("EDIT", 30).a,
                             uiManager->getTextSize("EDIT", 30).b / 2, {255, 255, 255}, 30);
        Cell *tmp = gameField->getElement(Cell::getRelativeLocation(uiManager->getInputManager()->getMouseCoords().x,
                                                                    uiManager->getInputManager()->getMouseCoords().y).a,
                                          Cell::getRelativeLocation(uiManager->getInputManager()->getMouseCoords().x,
                                                                    uiManager->getInputManager()->getMouseCoords().y).b);
        if (prevCell != tmp && prevCell != nullptr) {
            prevCell->applyNewState();
            startingState = tmp->state;
            tmp->state = 'h';
            tmp->next_state = startingState;
        }
        if (uiManager->getInputManager()->getMouseState() & SDL_BUTTON_LMASK) {
            if (tmp->next_state == 'a') {
                tmp->state = 'd';
                tmp->next_state = '-';
            }
            if (tmp->next_state == 'd') {
                tmp->state = 'a';
                tmp->next_state = '-';
            }
        }
        prevCell = tmp;

    }
};


#endif //PROGONHLANG_UI_EDIT_GAME_FIELD_HPP
