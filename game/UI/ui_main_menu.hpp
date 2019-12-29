//
// Created by vhundef on 27.12.2019.
//

#ifndef PROGONHLANG_UI_MAIN_MENU_HPP
#define PROGONHLANG_UI_MAIN_MENU_HPP


#include "ui_base.hpp"
#include "ui_button.hpp"

class UI_MainMenu : private virtual UI_Base {
public:
    void show() {
        play_btn->draw();
        test_btn->draw();
    }

public:
    uiButton *play_btn;
    uiButton *test_btn;

    UI_MainMenu(UI_Manager *ui_Manager, SDL_Window *window) : UI_Base(ui_Manager, window) {
        play_btn = new uiButton("Start", uiManager, uiManager->getWindowResolutionX() / 2 - 100, 150, 200, 50, 20);
        test_btn = new uiButton("Старт", uiManager, uiManager->getWindowResolutionX() / 2 - 100, 250, 200, 50, 20);
    }
};


#endif //PROGONHLANG_UI_MAIN_MENU_HPP
