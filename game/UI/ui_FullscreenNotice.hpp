//
// Created by vhund on 22.04.2020.
//

#ifndef PROGONHLANG_UI_FULLSCREENNOTICE_HPP
#define PROGONHLANG_UI_FULLSCREENNOTICE_HPP

#include "ui_base.hpp"
#include "ui_button.hpp"
class uiFullscreenNotice : private virtual UI_Base {
 private:
  string text;
  uiButton* okBTN{};

 public:
  uiFullscreenNotice(ScreenManager* _screenManager, const string& _text) {
	if (_screenManager == nullptr) {
	  throw runtime_error("ERROR: uiFullscreenNotice(ScreenManager*,string) ScreenManager is NULL");
	}
	screenManager = _screenManager;
	text = _text;
	okBTN = new uiButton("OK", screenManager, screenManager->getWindowResolutionX() / 2, screenManager->getWindowResolutionY() - 100, 100, 50, 20);

  }
  void show() {
	while (!screenManager->getInputManager()->quitEventCheck() &&!(okBTN->isHover() && screenManager->getInputManager()->getMouseState() & SDL_BUTTON_LMASK)) {
      SDL_SetRenderDrawColor(screenManager->getRenderer(), 255, 255, 255, 255);
	  if (SDL_RenderClear(screenManager->getRenderer()) < 0) {
		SDL_DestroyWindow(screenManager->getWindow());
		std::string error = SDL_GetError();
		SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
		throw std::runtime_error("Unable to clear screenManager->getRenderer() (SDL2)");
	  }
	  screenManager->getInputManager()->updateEvents();
	  okBTN->draw(screenManager->getInputManager()->getMouseCoords().x, screenManager->getInputManager()->getMouseCoords().y);
	  screenManager->printText(text, screenManager->getWindowResolutionX() / 2, screenManager->getWindowResolutionY() / 2, {0, 0, 0}, 20, true);
	  SDL_RenderPresent(screenManager->getRenderer());
	}
  }
};

#endif//PROGONHLANG_UI_FULLSCREENNOTICE_HPP
