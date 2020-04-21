//
// Created by vhundef on 24.12.2019.
//

#ifndef PROGONHLANG_UI_BASE_HPP
#define PROGONHLANG_UI_BASE_HPP


#include <string>
#include <map>
#include <utility>
#include <SDL_rect.h>
#include <SDL_surface.h>
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
 std::string locale{};
 ScreenManager *screenManager{};
 SDL_Window *win{};

 map<string, string> menuStrings;
};


#endif //PROGONHLANG_UI_BASE_HPP
