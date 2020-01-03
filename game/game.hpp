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
#include "UI/ui_edit_game_field.hpp"

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

        ren = SDL_CreateRenderer(win, -1, 0);
        if (ren == nullptr) {
            SDL_DestroyWindow(win);
            std::string error = SDL_GetError();
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
            throw std::runtime_error("Unable to create render (SDL2)");
        }

        uiManager = new UI_Manager(SDL_GetWindowSurface(win), ren, win,
                                   nullptr); //init UI_Manager and font related stuff
        gameField = new GameField(win, ren);
        gameField->checkForNeibourghs();
        inputManager = new InputManager();
        uiManager = new UI_Manager(SDL_GetWindowSurface(win), ren, win,
                                   inputManager); //init UI_Manager and font related stuff
        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "SDL2 init - Good\nGame Start");
        run(); // Starts the game
    }

private:
    int run() {
        Uint64 frameStart;
        Uint64 frameTime = 0;
        Uint64 curTime = 0;
        Uint64 endTime = 0;

        int frameDelay = 2;
        bool showDialog = true;
        UI_MainMenu uiMainMenu(uiManager, win, "ru");
        uiEditGameField uiEditGameField(uiManager, win, "ru", gameField);

        while (!inputManager->quitEventCheck()) {
               if (frameTime >= 100) {
                   state = 'q';
                   throw runtime_error("Game took too much time to render: " + to_string(frameTime));
               }

            frameStart = SDL_GetTicks();
            curTime = SDL_GetTicks();
            cout << "Frame delay: " << frameTime << endl;
            SDL_SetRenderDrawColor(ren, 80, 80, 253, 255);
            if (SDL_RenderClear(ren) < 0) {
                SDL_DestroyWindow(win);
                std::string error = SDL_GetError();
                SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
                throw std::runtime_error("Unable to clear render (SDL2)");
            }
            inputManager->updateEvents();
            if (state == 'r') {
                switch (inputManager->getEvent().key.keysym.sym) {
                    case SDLK_e:
                        if (inputManager->getEvent().type == SDL_KEYDOWN) {
                            state = 'e';
                            continue;
                        }
                        break;
                }
                showDialog = true;
                if (curTime >= endTime) {
                    endTime = SDL_GetTicks() + 90;
                    gameField->checkForNeibourghs();
                    gameField->drawBoard();
                } else {
                    gameField->drawBoard();
                }

                gameField->drawBoard();
                uiManager->printText("Cells: " + to_string(gameField->getAliveCells()), 10, 20, {247, 217, 63}, 25);
                SDL_RenderPresent(ren);
                prevCells = gameField->getAliveCells();
            }
            if (state == 'm') {
                uiMainMenu.show();
                state = uiMainMenu.act();

            }
            if (state == 'p') {
                
            }
            if (state == 'e') {
                switch (inputManager->getEvent().key.keysym.sym) {
                    case SDLK_c:
                        if (inputManager->getEvent().type == SDL_KEYDOWN)
                            gameField->clearBoard();
                        break;
                    case SDLK_e:
                        if (inputManager->getEvent().type == SDL_KEYDOWN) {
                            state = 'r';
                            continue;
                        }
                        break;
                }
                if (showDialog) {
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                             "EDIT MODE",
                                             "Включен режим редактирования.\nДля отчистки поля нажмите 'C'\nДля выхода из режима нажмите 'E",
                                             NULL);
                    gameField->checkForNeibourghs();
                    frameStart = SDL_GetTicks();
                }
                showDialog = false;

                gameField->drawBoard();
                uiManager->printText("Cells: " + to_string(gameField->countAliveCells()), 10, 20, {247, 217, 63}, 25);
                uiEditGameField.show();
            }
            if (state == 'q') break;

            SDL_RenderPresent(ren);
            frameTime = SDL_GetTicks() - frameStart;
            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
        }
        delete gameField;
        delete inputManager;
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
