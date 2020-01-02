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
#include "UI/ui_main_menu.hpp"
#include "input_manager.hpp"

class Game {
private:
    SDL_DisplayMode DM{};
    SDL_Window *win{};
    SDL_Renderer *ren{};
    GameField *gameField{};
    InputManager *inputManager{};
    UI_Manager *uiManager;
    char state = 'm';///< r-playing game| p-pause| m-main_Menu| e-Editing field
    int prevCells = 0;
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

        ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
        if (ren == nullptr) {
            SDL_DestroyWindow(win);
            std::string error = SDL_GetError();
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
            throw std::runtime_error("Unable to create render (SDL2)");
        }

        uiManager = new UI_Manager(SDL_GetWindowSurface(win), ren, win,
                                   nullptr); //init UI_Manager and font related stuff
        gameField = new GameField(win);
        inputManager = new InputManager();
        uiManager = new UI_Manager(SDL_GetWindowSurface(win), ren, win,
                                   inputManager); //init UI_Manager and font related stuff
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL2 init - Good\nGame Start");
        run(); // Starts the game
    }

private:
    int run() {
        UI_MainMenu uiMainMenu(uiManager, win, "ru");
        while (!inputManager->quitEventCheck()) {
            inputManager->updateEvents();
            if (state == 'r') {
                gameField->checkForNeibourghs();
                gameField->drawBoard();
                if (prevCells == gameField->getAliveCells()) {
                    cout << "Kinda STABLE CONFIG" << endl;
                }
                uiManager->printText("Cells: " + to_string(gameField->getAliveCells()), 10, 20, {247, 217, 63}, 25);
                SDL_RenderPresent(ren);
                prevCells = gameField->getAliveCells();
                SDL_Delay(90); // Decreasing cpu load
            }
            if (state == 'm') {
                uiMainMenu.show();
                SDL_Delay(10);

            }
            if (state == 'p') {

            }
            if (state == 'e') {

            }
            SDL_RenderPresent(ren);
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
