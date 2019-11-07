// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include "gtest/gtest.h"

#include <Poker/Games/Game.h>

using namespace Poker;

TEST(GameTests, BeginTurn)
{
    Game game{ GameConfig() };

    EXPECT_ANY_THROW(game.BeginTurn());

    game.AddPlayer<Player>();
    game.AddPlayer<Player>();
    game.AddPlayer<Player>();
    game.AddPlayer<Player>();

    EXPECT_NO_THROW(game.BeginTurn());

    EXPECT_EQ(game.LeftCards().size(), 52);
}

TEST(GameTests, AddPlayer)
{
    GameConfig config;
    Game game(config);

    game.AddPlayer<Player>();
    EXPECT_TRUE(game.GetPlayer(0).GetDeck().Empty());
    EXPECT_EQ(game.GetPlayer(0).GetMoney(), config.InitMoney);
}
