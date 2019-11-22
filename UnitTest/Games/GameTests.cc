// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include "gtest/gtest.h"

#include <Poker/Games/Game.h>
#include <Poker/Players/RandomPlayer.h>
#include <Poker/Task/Betting/BetTask.h>

using namespace Poker;

TEST(GameTests, AddPlayer)
{
    GameConfig config;
    config.AutoPlay = false;

    Game game(config);

    game.AddPlayer<RandomPlayer>();
    EXPECT_TRUE(game.GetPlayer(0).GetDeck().Empty());
    EXPECT_EQ(game.GetPlayer(0).GetMoney(), config.InitMoney);
}

TEST(GameTests, BeginTurn)
{
    GameConfig config;
    config.AutoPlay = false;

    Game game{ config };

    EXPECT_ANY_THROW(game.BeginTurn());

    game.AddPlayer<RandomPlayer>();
    game.AddPlayer<RandomPlayer>();
    game.AddPlayer<RandomPlayer>();
    game.AddPlayer<RandomPlayer>();

    EXPECT_NO_THROW(game.BeginTurn());

    EXPECT_EQ(game.LeftCards().size(),
              52u - config.InitCard * game.GetPlayerCount());
}

TEST(GameTests, OpenCards)
{
    GameConfig config;
    config.AutoPlay = false;

    Game game{ config };
    game.AddPlayer<RandomPlayer>();
    game.AddPlayer<RandomPlayer>();
    game.AddPlayer<RandomPlayer>();

    EXPECT_NO_THROW(game.BeginTurn());
    EXPECT_NO_THROW(game.OpenCard());

    EXPECT_EQ(game.LeftCards().size(),
              52 - config.InitCard * game.GetPlayerCount());

    for (std::size_t i = 0; i < game.GetPlayerCount(); ++i)
    {
        Player& player = game.GetPlayer(i);

        std::size_t openCards = 0;
        for (std::size_t cardID = 0; cardID < player.GetDeck().Size(); ++cardID)
        {
            openCards += player.GetDeck().GetCard(cardID).IsOpen();
        }

        EXPECT_EQ(openCards, 1u);
    }
}

TEST(GameTests, Betting)
{
    GameConfig config;
    config.AutoPlay = false;

    Game game{ config };
    game.AddPlayer<RandomPlayer>();
    game.AddPlayer<RandomPlayer>();
    game.AddPlayer<RandomPlayer>();

    EXPECT_NO_THROW(game.BeginTurn());
    EXPECT_NO_THROW(game.OpenCard());
    EXPECT_NO_THROW(game.PreBetting());

    EXPECT_EQ(
        game.LeftCards().size(),
        52 - config.InitCard * game.GetPlayerCount() - game.GetPlayerCount());

    for (std::size_t i = 0; i < game.GetPlayerCount(); ++i)
    {
        Player& player = game.GetPlayer(i);

        std::size_t openCards = 0;
        for (std::size_t cardID = 0; cardID < player.GetDeck().Size(); ++cardID)
        {
            openCards += player.GetDeck().GetCard(cardID).IsOpen();
        }

        EXPECT_EQ(openCards, 2u);
        EXPECT_TRUE(
            player.GetDeck().GetCard(player.GetDeck().Size() - 1).IsOpen());
    }
}

TEST(GameTests, ChoiceBetting)
{
    GameConfig config;
    config.AutoPlay = false;

    Game game{ config };
    game.AddPlayer<RandomPlayer>();
    game.AddPlayer<RandomPlayer>();
    game.AddPlayer<RandomPlayer>();

    EXPECT_NO_THROW(game.BeginTurn());
    EXPECT_NO_THROW(game.OpenCard());
    EXPECT_NO_THROW(game.PreBetting());

	EXPECT_TRUE(game.ChoiceBetting(TaskType::BET));
    EXPECT_TRUE(game.ChoiceBetting(TaskType::FOLD));
    EXPECT_TRUE(game.ChoiceBetting(TaskType::CHECK));

	EXPECT_FALSE(game.ChoiceBetting(TaskType::INVALID));
    EXPECT_FALSE(game.ChoiceBetting(TaskType::CALL));
    EXPECT_FALSE(game.ChoiceBetting(TaskType::RAISE));

    EXPECT_ANY_THROW(game.Process(std::make_unique<BetTask>(config.MinBetMoney - 1u).get()));
	EXPECT_NO_THROW(game.Process(std::make_unique<BetTask>(1000u).get()));
}
