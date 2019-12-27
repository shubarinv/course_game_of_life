//
// Created by vhundef on 27.12.2019.
//

#ifndef PROGONHLANG_UI_BUTTON_HPP
#define PROGONHLANG_UI_BUTTON_HPP


#include <SDL_rect.h>

class uiButton {
private:
	SDL_Rect body;
	SDL_Color defaultColor;
	SDL_Color hoverColor;
	SDL_Color disabledColor;
	bool enabled{true};
	bool hover{false};
public:
	bool isEnabled() const {
		return enabled;
	}

	void setEnabled(bool enabled) {
		uiButton::enabled = enabled;
	}

	bool isHover() const {
		return hover;
	}

	bool collisionCheck() {
		return !enabled;
	}

	void draw();


};


#endif //PROGONHLANG_UI_BUTTON_HPP
