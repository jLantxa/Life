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

#define ALIVE true
#define DEAD  false

static constexpr unsigned int DELAY = 100;

static constexpr unsigned int WINDOW_WIDTH  = 640;
static constexpr unsigned int WINDOW_HEIGHT = 640;

class Life {
public:
    Life(uint16_t width, uint16_t height)
    :   mWidth(width),
        mHeight(height),
        mCellWidth(WINDOW_WIDTH / width),
        mCellHeight(WINDOW_HEIGHT / height),
        mBitBoard(width, height),
        mBitBoardTmp(width, height)
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0) {
            std::cout << "Failed to initialize the SDL2 library\n";
        }

        mWindow = SDL_CreateWindow(
            "Life",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            0);

        if(!mWindow) {
            std::cout << "Failed to create window\n";
        }

        mRenderer = SDL_CreateRenderer(mWindow, -1, 0);

        DrawBackground();
        Init();
    }

    ~Life() = default;

    void Run() {
        unsigned int cycles = 0;
        while (true) {
            cycles++;
            std::cout << "Cycles: " << cycles << std::endl;
            Draw();
            SDL_RenderPresent(mRenderer);

            HandleEvents();
            if (!bRun) break;
            UpdateState();
            SDL_Delay(DELAY);
        }

        SDL_Quit();
    }

private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    uint16_t mWidth, mHeight;
    const unsigned int mCellWidth;
    const unsigned int mCellHeight;

    bool bRun = true;

    BitBoard mBitBoard;
    BitBoard mBitBoardTmp;

    void Quit() {
        bRun = false;
        std::cout << "QUIT" << std::endl;
    }

    void HandleEvents() {
        SDL_Event event;
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    Quit();
                }
                break;

            case SDL_QUIT:
                Quit();
        }
    }

    unsigned int GetNumberOfAliveNeighbours(uint16_t i, uint16_t j) {
        unsigned int alive = 0;
        for (int x = -1; x <= 1; x++) {
            for (int y = -1; y <= 1; y++) {
                if (mBitBoard.GetState((i+x) % mWidth, (j+y) % mHeight)) {
                    alive++;
                }
            }
        }
        return alive;
    }

    void UpdateState() {
        mBitBoardTmp = mBitBoard;
        for (unsigned int i = 0; i < mWidth; i++) {
            for (unsigned int j = 0; j < mHeight; j++) {
                unsigned int aliveNeighbours = GetNumberOfAliveNeighbours(i, j);
                bool state = mBitBoard.GetState(i, j);
                if (state == DEAD)
                {
                    if(aliveNeighbours >= 2 && aliveNeighbours <= 3) {
                        mBitBoardTmp.SetState(i, j, ALIVE);
                    }
                }
                else if(state == ALIVE)
                {
                    if(aliveNeighbours < 2 || aliveNeighbours > 3) {
                        mBitBoardTmp.SetState(i, j, DEAD);
                    }
                }
            }
        }
        mBitBoard = mBitBoardTmp;
    }

    void Draw() {
        DrawBackground();
        for (unsigned int i = 0; i < mWidth; i++) {
            for (unsigned int j = 0; j < mHeight; j++) {
                DrawCell(i, j);
            }
        }
    }

    void DrawBackground() {
        SDL_SetRenderDrawColor(mRenderer, 16, 16, 16, 255);
        SDL_RenderClear(mRenderer);
    }

    void DrawCell(unsigned int i, unsigned int j) {
        bool isAlive = mBitBoard.GetState(i, j);

        SDL_Rect rect {
            static_cast<int>(i * mCellWidth),
            static_cast<int>(j * mCellHeight),
            static_cast<int>(mCellWidth - 1),
            static_cast<int>(mCellHeight - 1)
        };

        SDL_SetRenderDrawColor(mRenderer, 192, 192, 192, 255);
        if (isAlive) {
            SDL_RenderFillRect(mRenderer, &rect);
        }
        SDL_SetRenderDrawColor(mRenderer, 64, 64, 64, 255);
        SDL_RenderDrawRect(mRenderer, &rect);
    }

    void Init() {
        //mBitBoard.SetState(10, 10, ALIVE);
        //mBitBoard.SetState(11, 10, ALIVE);
        //mBitBoard.SetState(12, 10, ALIVE);
    }
};

int main(int argc, char const *argv[])
{
    Life life(64, 64);
    life.Run();

    return 0;
}
