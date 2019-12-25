//
// Created by vhundef on 24.12.2019.
//

#ifndef PROGONHLANG_GAME_HPP
#define PROGONHLANG_GAME_HPP


#include <SDL.h>
#include <iostream>
#include <stdexcept>
#include "UI/ui_manager.hpp"
#include "game_field.hpp"

class Game {
private:
	SDL_DisplayMode DM{};
	SDL_Window *win{};
	SDL_Renderer *ren{};
	GameField* gameField{};
	UI_Manager *uiManager;
	bool runGame = false;
public:
	Game() {
		std::cout << "Trying to init SDL2..." << std::endl;
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::string error = SDL_GetError();
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
			throw std::runtime_error("Unable to init SDL2");
		}
		SDL_GetCurrentDisplayMode(0, &DM);
		auto Width = DM.w;
		auto Height = DM.h;
		win = SDL_CreateWindow("The Game Of Life", 0, 0, 1280, 720, SDL_WINDOW_SHOWN);

		if (win == nullptr) {
			std::string error = SDL_GetError();
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
			throw std::runtime_error("Unable to create window (SDL2)");
		}

		ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (ren == nullptr) {
			SDL_DestroyWindow(win);
			std::string error = SDL_GetError();
			SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
			throw std::runtime_error("Unable to create render (SDL2)");
		}

		uiManager = new UI_Manager(SDL_GetWindowSurface(win), ren); //init UI_Manager and font related stuff
		gameField=new GameField();
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL2 init - Good\nGame Start");
		run(); // Starts the game
	}

private:
	int run() {
		runGame = true;
		SDL_Event event;
		while (runGame) {
			SDL_PollEvent(&event);
			uiManager->printText("Тест Вывода русского", 100, 100, {0, 255, 0}, 20);
			uiManager->printText("English output test", 100, 140, {0, 255, 0}, 20);
			gameField->drawBoard();
			SDL_RenderPresent(ren);

			/// TODO - Создать класс для отработки событий и вынести это условие туда
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
				runGame = false;
				SDL_LogInfo(SDL_LOG_CATEGORY_INPUT, "Got QUIT event");
			}

			SDL_Delay(5); // Decreasing cpu load
		}

		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Destroying render");
		SDL_DestroyRenderer(ren);
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Render Destroyed\nDestroying window");
		SDL_DestroyWindow(win);
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Destroyed window");
		free(uiManager);
		return 0;
	}
};


#endif //PROGONHLANG_GAME_HPP
