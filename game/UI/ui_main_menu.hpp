//
// Created by vhundef on 27.12.2019.
//

#ifndef PROGONHLANG_UI_MAIN_MENU_HPP
#define PROGONHLANG_UI_MAIN_MENU_HPP


#include <utility>

#include "ui_base.hpp"
#include "ui_button.hpp"

class UI_MainMenu : private virtual UI_Base {
public:
	void show() {
		play_btn->draw(uiManager->getInputManager()->getMouseCoords().x,
		               uiManager->getInputManager()->getMouseCoords().y);
		quit_btn->draw(uiManager->getInputManager()->getMouseCoords().x,
		               uiManager->getInputManager()->getMouseCoords().y);
		uiManager->printText("Made by Vladimir Shubarin in 2020",
		                     uiManager->getWindowResolutionX() / 2 -
		                     uiManager->getTextSize("Made by Vladimir Shubarin in 2020", 20).a / 2,
		                     uiManager->getWindowResolutionY() - 30, {255, 255, 255}, 20);
	}

	char act() {
		if (play_btn->isHover() && uiManager->getInputManager()->getMouseState() & SDL_BUTTON_LMASK) {
			/*SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			                         "Rules",
			                         "You can edit field by pressing E.",
			                         NULL);*/
			return 'r';
		} else if (quit_btn->isHover() &&
		           uiManager->getInputManager()->getMouseState() & SDL_BUTTON_LMASK) { return 'q'; }
		else return 'm';
	}

	uiButton *play_btn;
	uiButton *quit_btn;

	UI_MainMenu(UI_Manager *ui_Manager, SDL_Window *window, std::string _locale) : UI_Base(ui_Manager, window,
	                                                                                       std::move(_locale)) {
		if (locale == "en") {
			play_btn = new uiButton(menuStrings["Start_En"], uiManager, uiManager->getWindowResolutionX() / 2 - 100,
			                        150, 200, 50, 20);
			quit_btn = new uiButton(menuStrings["Quit_En"], uiManager, uiManager->getWindowResolutionX() / 2 - 100, 250,
			                        200, 50, 20);
		} else {
			play_btn = new uiButton(menuStrings["Start_Ru"], uiManager, uiManager->getWindowResolutionX() / 2 - 100,
			                        150, 200, 50, 20);
			quit_btn = new uiButton(menuStrings["Quit_Ru"], uiManager, uiManager->getWindowResolutionX() / 2 - 100, 250,
			                        200, 50, 20);
		}

	}

	~UI_MainMenu() {
		delete play_btn;
		delete quit_btn;
	}
};


#endif //PROGONHLANG_UI_MAIN_MENU_HPP
