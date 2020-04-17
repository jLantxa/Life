/*
 * Life
 * Copyright (C) 2020  Javier Lancha Vázquez
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <SDL2/SDL.h>

#include "BitBoard.hpp"

#include <cstdint>

#include <iostream>

class Life {
public:
    Life(uint16_t width, uint16_t height)
    :   mWidth(width),
        mHeight(height),
        mBitBoard(width, height)
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "Failed to initialize the SDL2 library\n";
        }

        mWindow = SDL_CreateWindow(
            "Life",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            640, 640,
            0);

        if(!mWindow) {
            std::cout << "Failed to create window\n";
        }

        SDL_Surface *mSurface = SDL_GetWindowSurface(mWindow);

        if(!mSurface) {
            std::cout << "Failed to get the surface from the window\n";
        }
    }

    ~Life() = default;

    void Run() {
        SDL_Event event;

        while (true) {
            HandleEvents(event);
            if (!bRun) break;

            UpdateState();
            Draw();

            SDL_UpdateWindowSurface(mWindow);

            SDL_Delay(16);
        }
    }

private:
    SDL_Window* mWindow;
    SDL_Surface* mSurface;

    uint16_t mWidth, mHeight;

    bool bRun = true;

    BitBoard mBitBoard;

    void HandleEvents(SDL_Event& event) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_KEYDOWN:
                break;

            case SDL_QUIT:
                bRun = false;
        }
    }

    void UpdateState() {

    }

    void Draw() {
        for (uint16_t i = 0; i < mWidth; i++) {
            for (uint16_t j = 0; j < mHeight; j++) {

            }
        }
    }
};

int main(int argc, char const *argv[])
{
    Life life(64, 64);
    life.Run();

    return 0;
}
