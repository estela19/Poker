// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include "gtest/gtest.h"

#include <Poker/Games/Game.h>

using namespace Poker;

TEST(GameTests, BeginTurn)
{
    Game game;

    game.BeginTurn();

    EXPECT_EQ(game.LeftCards().size(), 52);
}

TEST(GameTests, AddPlayer)
{
    Game game;

    game.AddPlayer<Player>();
}
