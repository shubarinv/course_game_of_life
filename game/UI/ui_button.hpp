//
// Created by vhundef on 27.12.2019.
//

#ifndef PROGONHLANG_UI_BUTTON_HPP
#define PROGONHLANG_UI_BUTTON_HPP


#include <SDL_rect.h>
#include <string>

class uiButton {
private:
	SDL_Rect body;
	SDL_Color defaultColor;
	SDL_Color hoverColor;
	SDL_Color disabledColor;
	std::string text = "UNSET";
	bool enabled{true};
	bool hover{false};
public:
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
			if (hover) {///TODO paint button with hover color
			} else {///TODO paint button with default color
			}
		} else {
			///TODO paint button with disabled color
		}
	}


};


#endif //PROGONHLANG_UI_BUTTON_HPP
