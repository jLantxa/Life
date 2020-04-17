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

#ifndef _LIFE_INCLUDE_BITBOARD_HPP_
#define _LIFE_INCLUDE_BITBOARD_HPP_

#include <cstdint>

class BitBoard {
public:
    BitBoard(uint16_t width, uint16_t height);
    ~BitBoard();

    bool GetState(uint16_t i, uint16_t j) const;
    void SetState(uint16_t i, uint16_t j, bool state);

    uint16_t Width() const;
    uint16_t Height() const;

private:
    using Word = uint64_t;
    static constexpr std::size_t WordSize = sizeof(Word);

    Word* mBoard;
    uint16_t mWidth;
    uint16_t mHeight;
};

#endif  // _LIFE_INCLUDE_BITBOARD_HPP_
