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

#include <gtest/gtest.h>

#include "BitBoard.hpp"

#include <memory>

static constexpr uint16_t WIDTH  = 64;
static constexpr uint16_t HEIGHT = 64;

class BitBoardTest : public ::testing::Test {
public:
    BitBoardTest() = default;
    ~BitBoardTest() = default;

    std::unique_ptr<BitBoard> bitBoard = std::make_unique<BitBoard>(WIDTH, HEIGHT);
};

TEST_F(BitBoardTest, BoardDimensions) {
    EXPECT_EQ(bitBoard->Width(), WIDTH);
    EXPECT_EQ(bitBoard->Height(), HEIGHT);
}

TEST_F(BitBoardTest, BoardInitStateFalse) {
    for (uint16_t i = 0; i < WIDTH; i++) {
        for (uint16_t j = 0; j < HEIGHT; j++) {
            ASSERT_FALSE(bitBoard->GetState(i, j));
        }
    }
}

TEST_F(BitBoardTest, BoardSetState) {
    for (uint16_t i = 0; i < WIDTH; i++) {
        for (uint16_t j = 0; j < HEIGHT; j++) {
            ASSERT_FALSE(bitBoard->GetState(i, j));
        }
    }

    bitBoard->SetState(25, 52, true);
    for (uint16_t i = 0; i < WIDTH; i++) {
        for (uint16_t j = 0; j < HEIGHT; j++) {
            if (i == 25 && j == 52) {
                ASSERT_TRUE(bitBoard->GetState(i, j));
            } else {
                ASSERT_FALSE(bitBoard->GetState(i, j));
            }
        }
    }

    bitBoard->SetState(25, 52, false);
    for (uint16_t i = 0; i < WIDTH; i++) {
        for (uint16_t j = 0; j < HEIGHT; j++) {
            ASSERT_FALSE(bitBoard->GetState(i, j));
        }
    }
}
