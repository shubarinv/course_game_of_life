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
	play_btn->draw(screenManager->getInputManager()->getMouseCoords().x, screenManager->getInputManager()->getMouseCoords().y);
	quit_btn->draw(screenManager->getInputManager()->getMouseCoords().x, screenManager->getInputManager()->getMouseCoords().y);

	screenManager->printText("//todo upd copyright", screenManager->getWindowResolutionX() / 2 - screenManager->getTextSize("//todo upd copyright", 20).a / 2, screenManager->getWindowResolutionY() - 30, {255, 255, 255}, 20);
  }

  char act() {
	if (play_btn->isHover() && screenManager->getInputManager()->getMouseState() & SDL_BUTTON_LMASK) {
	  SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "1");
	  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Rules", "You can edit field by pressing E.", NULL);
	  SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
	  return 'r';

	} else if (quit_btn->isHover() && screenManager->getInputManager()->getMouseState() & SDL_BUTTON_LMASK) {
	  return 'q';

	} else
	  return 'm';
  }

  uiButton *play_btn;
  uiButton *quit_btn;

  explicit UI_MainMenu(ScreenManager *_screenManager) {
	screenManager=_screenManager;
	play_btn = new uiButton(menuStrings["Start_En"], screenManager, screenManager->getWindowResolutionX() / 2 - 100, 150, 200, 50, 20);
	quit_btn = new uiButton(menuStrings["Quit_En"], screenManager, screenManager->getWindowResolutionX() / 2 - 100, 250, 200, 50, 20);
  }

  ~UI_MainMenu() {
	delete play_btn;
	delete quit_btn;
  }
};

#endif// PROGONHLANG_UI_MAIN_MENU_HPP
