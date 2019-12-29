//
// Created by vhundef on 27.12.2019.
//

#ifndef PROGONHLANG_UI_BUTTON_HPP
#define PROGONHLANG_UI_BUTTON_HPP


#include <SDL_rect.h>
#include <string>
#include "ui_manager.hpp"

class uiButton {
private:
    SDL_Rect body{};
    SDL_Color defaultColor{127, 179, 114};
    SDL_Color hoverColor{89, 150, 74};
    SDL_Color disabledColor{82, 82, 82};
    UI_Manager *uiManager{};
    std::string text = "UNSET";
    bool enabled{true};
    bool hover{false};
public:
    uiButton(std::string string, UI_Manager *_uiManager, int x, int y, int width, int height) {
        if (_uiManager == nullptr) {
            std::string error = "UIButton->Constructor->uiManager is null";
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
            throw std::runtime_error("Unable to button uiManager is null");
        }
        uiManager = _uiManager;
        body.x=x;
        body.y=y;
        body.w=width;
        body.h=height;
    }

    [[nodiscard]] bool isEnabled() const {
        return enabled;
    }

    void setEnabled(bool _enabled) {
        uiButton::enabled = _enabled;
    }

    [[nodiscard]] bool isHover() const {
        return hover;
    }

    bool collisionCheck() {
        return !enabled;
    }

    void calculateTextPosition() {
        /// Todo: somehow figure out how to position text at the center of the button
    }

    void draw() {
        if (enabled) {
            if (hover) {SDL_FillRect(SDL_GetWindowSurface(uiManager->getWindow()), &body,UI_Manager::rgbToHex(hoverColor));
            } else {SDL_FillRect(SDL_GetWindowSurface(uiManager->getWindow()), &body,UI_Manager::rgbToHex(defaultColor));
            }
        } else {
            SDL_FillRect(SDL_GetWindowSurface(uiManager->getWindow()), &body,UI_Manager::rgbToHex(disabledColor));
        }
    }

    void setDefaultColor(const SDL_Color &_defaultColor) {
        uiButton::defaultColor = _defaultColor;
    }

    void setHoverColor(const SDL_Color &_hoverColor) {
        uiButton::hoverColor = _hoverColor;
    }

    void setDisabledColor(const SDL_Color &_disabledColor) {
        uiButton::disabledColor = _disabledColor;
    }

};


#endif //PROGONHLANG_UI_BUTTON_HPP
