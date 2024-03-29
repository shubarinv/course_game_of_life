#include <SDL_rect.h>
#include <SDL_surface.h>
#include <string>
#include <SDL_log.h>
#include <stdexcept>
#include <SDL_video.h>

class Cell {
    struct twoInt {
        int a, b;
    };
private:
    SDL_Rect block{};
    SDL_Window *window;
    SDL_Renderer *renderer;
    int aliveFor{0};
    char state = 'd';
public:
    void setState(char _state) {
        Cell::state = _state;
    }

public:
    char getState() const {
        if (state != 'd' && state != 'u' && state != 'h')return 'a';
        else return state;
    }
    ///< a-alive d-dead b-born h-hover
public:
    char next_state = '-'; ///< a-alive d-dead b-born h-hover
    char deathReason = 'u'; // l= not enough neighbours; u= unset; c=to much cells nearby
    Cell(SDL_Window *game_window, SDL_Renderer *_renderer) {
        block.h = 16;
        block.w = block.h;
        window = game_window;
        renderer = _renderer;
    }

    void redraw() {
        SDL_RenderDrawRect(renderer, &block);
        switch (state) {
            case 'd':
                // Set render color to blue ( rect will be rendered in this color )
                SDL_SetRenderDrawColor(renderer, 64, 68, 67, 255);
                aliveFor = 0;
                break;
            case 'h':
                SDL_SetRenderDrawColor(renderer, 224, 187, 0, 255);
                break;
            case 'b':
                SDL_SetRenderDrawColor(renderer, 4, 141, 204, 255);
                aliveFor++;
                state = 'a';
                break;
        }
        if (state == 'a') {
            if (aliveFor >= 0 && aliveFor <= 20) { SDL_SetRenderDrawColor(renderer, 14, 255, 0, 255); }
            else if (aliveFor > 20 && aliveFor <= 40) SDL_SetRenderDrawColor(renderer, 8, 144, 0, 255);
            else if (aliveFor > 40 && aliveFor <= 60) SDL_SetRenderDrawColor(renderer, 10, 93, 0, 255);
            else if (aliveFor > 60 && aliveFor <= 80) SDL_SetRenderDrawColor(renderer, 7, 70, 0, 255);
            else if (aliveFor > 80) SDL_SetRenderDrawColor(renderer, 6, 59, 0, 255);
            aliveFor++;
        }
        // Render rect
        SDL_RenderFillRect(renderer, &block);
    }

    void setLocation(int x, int y) {
        int h, w;
        SDL_GetWindowSize(window, &w, &h);
        if (x * block.h <= w && x * block.h >= 0 &&
            y * block.h <= h &&
            y * block.h >= 0) {
            block.x = x * block.h;
            block.y = y * block.h;
        } else {
            std::string error = "Cell->SetLocationFailed new coords are out of bounds X:" + std::to_string(x) + " Y:" +
                                std::to_string(y * block.h) + " while max is: " + std::to_string(w) + "x" +
                                std::to_string(h);
            SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "%s", error.c_str());
            throw std::runtime_error("Cell->SetLocationFailed new coords are out of bounds");
        }
    }

    static twoInt getRelativeLocation(int x, int y) {
        return {x / 16, y / 16};
    }

    void applyNewState() {
        if (next_state != '-')state = next_state;
        next_state = '-';
    }
};