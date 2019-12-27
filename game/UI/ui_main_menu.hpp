//
// Created by vhundef on 27.12.2019.
//

#ifndef PROGONHLANG_UI_MAIN_MENU_HPP
#define PROGONHLANG_UI_MAIN_MENU_HPP


#include "ui_base.hpp"

class UI_MainMenu : private virtual UI_Base {
public:
	void show() {
		createButton(uiManager->getWindowResolutionX()/2-100,100,200,50,"START",0x00f0ff,{255,0,225});
/*
		drawText((int) (0.5 * screenManager->screenUnit * 3 - 5),
		         (int) (3 * screenManager->screenUnit +
		                screenManager->screenUnit * 0.4),
		         "leaderboard", 0xffffff);
		drawText(
				(int) (0.5 * screenManager->screenUnit * 3 - 5),
				(int) (3 * screenManager->screenUnit + screenManager->screenUnit * 0.8),
				"rules", 0xffffff);

		drawText((int) (0.5 * screenManager->screenUnit),
		         (int) (3 * screenManager->screenUnit + screenManager->screenUnit * 1.2),
		         "quit", 0xffffff);
*/
	}

public:
	UI_MainMenu(UI_Manager *ui_Manager, SDL_Window *window) : UI_Base(ui_Manager, window) {
	}
};


#endif //PROGONHLANG_UI_MAIN_MENU_HPP
