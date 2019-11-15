// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include "gtest/gtest.h"

#include <Poker/Games/Game.h>
#include <Poker/Players/RandomPlayer.h>

using namespace Poker;

TEST(GameTests, BeginTurn)
{
    Game game{ GameConfig() };

    EXPECT_ANY_THROW(game.BeginTurn());

    game.AddPlayer<RandomPlayer>();
    game.AddPlayer<RandomPlayer>();
    game.AddPlayer<RandomPlayer>();
    game.AddPlayer<RandomPlayer>();

    EXPECT_NO_THROW(game.BeginTurn());
	
    EXPECT_EQ(game.LeftCards().size(), 52);
}

TEST(GameTests, AddPlayer)
{
    GameConfig config;
    Game game(config);

    game.AddPlayer<RandomPlayer>();
    EXPECT_TRUE(game.GetPlayer(0).GetDeck().Empty());
    EXPECT_EQ(game.GetPlayer(0).GetMoney(), config.InitMoney);
}
