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

#include "BitBoard.hpp"

#include <cmath>

#include <algorithm>

BitBoard::BitBoard(uint16_t width, uint16_t height)
:   mWidth(width),
    mHeight(height),
    mNumWords(std::ceil(8.0f * (width * height) / WordSize))
{
    mBoard = new Word[mNumWords];
    std::fill(mBoard, mBoard + mNumWords, 0);
}

BitBoard::~BitBoard() {
    delete mBoard;
}

uint16_t BitBoard::Width() const {
    return mWidth;
}

uint16_t BitBoard::Height() const {
    return mHeight;
}

bool BitBoard::GetState(uint16_t i, uint16_t j) const {
    const std::size_t board_index = mWidth*i + j;
    const std::size_t word_number = board_index / WordSize;
    const uint8_t word_index = board_index % WordSize;

    return mBoard[word_number] & (1 << word_index);
}

void BitBoard::SetState(uint16_t i, uint16_t j, bool state) {
    const std::size_t board_index = mWidth*i + j;
    const std::size_t word_number = board_index / WordSize;
    const uint8_t word_index = board_index % WordSize;

    if (state == true) {
        mBoard[word_number] |= (1 << word_index);
    } else {
        mBoard[word_number] &= ~(static_cast<Word>(1) << word_index);
    }
}

BitBoard& BitBoard::operator=(BitBoard& other) {
    std::copy(
        other.mBoard,
        other.mBoard + std::min(mNumWords, other.mNumWords),
        mBoard);

    return *this;
}
