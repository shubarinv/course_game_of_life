//
// Created by vhundef on 24.12.2019.
//

#ifndef PROGONHLANG_GAME_HPP
#define PROGONHLANG_GAME_HPP

#include <SDL.h>

#include <iostream>
#include <stdexcept>

#include "UI/ui_edit_game_field.hpp"
#include "UI/ui_main_menu.hpp"
#include "UI/ui_manager.hpp"
#include "game_field.hpp"
#include "input_manager.hpp"

class Game {
 private:
  GameField *gameField{};
  InputManager *inputManager{};
  ScreenManager *screenManager;
  Uint64 eButtonPress = 0;
  std::vector<std::vector<Cell>> gameFieldSave;
  char state = 'm';///< r-playing game| p-pause| m-main_Menu| e-Editing field
 public:
  Game() {
	std::cout << "Trying to init SDL2..." << std::endl;
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
	  std::string error = SDL_GetError();
	  SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
	  throw std::runtime_error("Unable to init SDL2");
	}
    inputManager = new InputManager();
    screenManager = new ScreenManager(inputManager);//init ScreenManager and font related stuff
	gameField = new GameField(screenManager);
	gameField->checkRulesCompliance();

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL2 init - Good\nGame Start");
	run();// Starts the game
  }

 private:
  int run() {
	Uint64 frameStart;
	Uint64 frameTime = 0;
	Uint64 curTime = 0;
	Uint64 endTime = 0;

	int frameDelay = 2;
	bool showDialog = true;
	Uint64 lastSave = SDL_GetTicks();

	UI_MainMenu uiMainMenu(screenManager);
	uiEditGameField uiEditGameField(screenManager, gameField);

	SDL_RaiseWindow(screenManager->getWindow());

	while (!inputManager->quitEventCheck()) {
	  SDL_SetRenderDrawColor(screenManager->getRenderer(), 255, 255, 255, 255);
	  if (SDL_RenderClear(screenManager->getRenderer()) < 0) {
		SDL_DestroyWindow(screenManager->getWindow());
		std::string error = SDL_GetError();
		SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
		throw std::runtime_error("Unable to clear screenManager->getRenderer()der (SDL2)");
	  }
	  frameStart = SDL_GetTicks();
	  curTime = SDL_GetTicks();
	  cout << "Frame delay: " << frameTime << endl;
	  cout << "State: " << state << endl;
	  inputManager->updateEvents();
	  if (state == 'r') {
		switch (inputManager->getEvent().key.keysym.sym) {
		  case SDLK_e:
			if (inputManager->getEvent().type == SDL_KEYDOWN && SDL_GetTicks() - eButtonPress > 1000) {
			  state = 'e';
			  eButtonPress = SDL_GetTicks();
			  continue;
			}
			break;
		  case SDLK_s:
			if (SDL_GetTicks() - lastSave >= 2000) {
			  //gameField->save();
			  cout << "Saved!" << endl;
			  lastSave = SDL_GetTicks();
			}
		}
		showDialog = true;
		if (curTime >= endTime) {
		  endTime = SDL_GetTicks() + 90;
		  gameField->checkRulesCompliance();
		  gameField->drawBoard();
		} else {
		  gameField->drawBoard();
		}

		gameField->drawBoard();
		screenManager->printText("Cells: " + to_string(gameField->getAliveCells()), 10, 20, {0, 0, 0}, 25);
	  }
	  if (state == 'm') {
		//gameField->drawBoard();
		//gameField->checkRulesCompliance();
		uiMainMenu.show();
		state = uiMainMenu.act();

		if (state == 'r') {
		  gameField->clearBoard();
		  gameField->randomiseField();
		}
	  }

	  if (inputManager->getEvent().key.keysym.sym == SDLK_e && inputManager->getEvent().type == SDL_KEYDOWN && state == 'e' && SDL_GetTicks() - eButtonPress > 1000) {
		eButtonPress = SDL_GetTicks();
		state = 'r';
		if (gameField->countAliveCells() > 300)
		  screenManager->printText("Wait a sec please...", screenManager->getWindowResolutionX() / 2 - screenManager->getTextSize("Wait a sec please...", 40).a, screenManager->getWindowResolutionY() / 2 - 20, {255, 0, 0}, 40);
		SDL_RenderPresent(screenManager->getRenderer());
		continue;
	  }
	  if (state == 'r') {
	  }
	  if (state == 'e') {
		switch (inputManager->getEvent().key.keysym.sym) {
		  case SDLK_c:
			if (inputManager->getEvent().type == SDL_KEYDOWN) {
			  gameField->clearBoard();
			}
			break;
		  case SDLK_r:
			if (inputManager->getEvent().type == SDL_KEYDOWN) {
			  gameField->setField(gameFieldSave);
			}
			break;
		}
		if (showDialog) {
		  SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "1");
		  SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
								   "EDIT MODE",
								   "You are entering edit mode.\nTo clear field press 'C'\nTo reset all changes press 'R'\nTo quit press 'E'",
								   NULL);
		  SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");
		  gameFieldSave = gameField->getField();
		  frameStart = SDL_GetTicks();
		}
		showDialog = false;

		gameField->drawBoard();
		screenManager->printText("Cells: " + to_string(gameField->countAliveCells()), 10, 20, {247, 217, 63}, 25);
		uiEditGameField.show();
	  }
	  if (state == 'q') break;

	  SDL_RenderPresent(screenManager->getRenderer());
	  frameTime = SDL_GetTicks() - frameStart;
	  if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
	  }
	}
	delete gameField;
	delete inputManager;
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Destroying renderer");
	SDL_DestroyRenderer(screenManager->getRenderer());
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Render Destroyed\nDestroying window");
	SDL_DestroyWindow(screenManager->getWindow());
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Destroyed window");
	free(screenManager);
	return 0;
  }
};

#endif//PROGONHLANG_GAME_HPP
