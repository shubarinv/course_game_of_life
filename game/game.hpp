//
// Created by vhundef on 24.12.2019.
//

#ifndef PROGONHLANG_GAME_HPP
#define PROGONHLANG_GAME_HPP


#include <SDL.h>
#include <iostream>
#include <stdexcept>

class Game {
private:
	SDL_DisplayMode DM{};
	SDL_Window *win{};
	SDL_Renderer *ren{};
	bool runGame = false;
public:
	Game() {
		std::cout << "Trying to init SDL2..." << std::endl;
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
			throw std::runtime_error("Unable to init SDL2");
		}
		SDL_GetCurrentDisplayMode(0, &DM);
		auto Width = DM.w;
		auto Height = DM.h;

		win = SDL_CreateWindow("The Game Of Life", 0, 0, 640, 480, SDL_WINDOW_SHOWN);

		if (win == nullptr) {
			std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
			throw std::runtime_error("Unable to create window (SDL2)");
		}

		ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (ren == nullptr) {
			SDL_DestroyWindow(win);
			std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
			throw std::runtime_error("Unable to create render (SDL2)");
		}
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL2 init - Good\nGame Start");
		run(); // Starts the game
	}

private:
	int run() {
		runGame = true;
		SDL_Event event;
		while (runGame) {
			SDL_PollEvent(&event);
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
		return 0;
	}
};


#endif //PROGONHLANG_GAME_HPP
