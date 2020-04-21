//
// Created by vhundef on 24.12.2019.
//

#ifndef PROGONHLANG_UI_BASE_HPP
#define PROGONHLANG_UI_BASE_HPP

#include <SDL_rect.h>
#include <SDL_surface.h>

#include <map>
#include <string>
#include <utility>

#include "ui_manager.hpp"

class UI_Base {
 public:
  UI_Base() {

	menuStrings["Start_En"] = "Start";
	menuStrings["Start_Ru"] = "Начать";

	menuStrings["Quit_En"] = "Quit";
	menuStrings["Quit_Ru"] = "Выход";

	menuStrings["Settings_En"] = "Settings";
	menuStrings["Settings_Ru"] = "Настройки";
  }

 protected:
  ScreenManager *screenManager{};
  [[deprecated]] map<string, string> menuStrings;
};

#endif//PROGONHLANG_UI_BASE_HPP
