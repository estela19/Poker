// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include "gtest/gtest.h"

#include <Poker/Games/Game.h>

using namespace Poker;

TEST(GameTests, AddPlayer)
{
    Game game;

    game.AddPlayer<Player>();
}
