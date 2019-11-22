// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include "gtest/gtest.h"

#include <Poker/Games/Turn.h>
#include <Poker/Players/RandomPlayer.h>

#include <iostream>

using namespace Poker;

TEST(TurnTests, Insert)
{
    Turn turn;

    Player::Ptr player1 = std::make_unique<RandomPlayer>();
    Player::Ptr player2 = std::make_unique<RandomPlayer>();

    player1->SetMoney(10000u);
    player2->SetMoney(20000u);

    EXPECT_NO_THROW(turn.Insert(player1));
    std::cerr << turn.Current()->ToString() << std::endl;
    EXPECT_NO_THROW(turn.Insert(player2));
    std::cerr << turn.Current()->ToString() << std::endl;

    EXPECT_EQ(turn.GetSize(), 2);
    EXPECT_EQ(turn.Current()->GetMoney(), 20000u);
}

TEST(TurnTests, Pop)
{
    Turn turn;

    Player::Ptr player1 = std::make_unique<RandomPlayer>();
    Player::Ptr player2 = std::make_unique<RandomPlayer>();

    EXPECT_NO_THROW(turn.Insert(player1));
    EXPECT_NO_THROW(turn.Insert(player2));

    player1->SetMoney(10000u);
    player2->SetMoney(20000u);

    EXPECT_NO_THROW(turn.Pop());
    EXPECT_EQ(turn.GetSize(), 1);

    EXPECT_EQ(turn.Current()->GetMoney(), 10000u);
}

TEST(TurnTests, DeadPlayer)
{
    Turn turn;

    Player::Ptr player1 = std::make_unique<RandomPlayer>();
    Player::Ptr player2 = std::make_unique<RandomPlayer>();
    Player::Ptr player3 = std::make_unique<RandomPlayer>();

    player1->SetMoney(10000u);
    player2->SetMoney(20000u);
    player3->SetMoney(30000u);

    turn.Insert(player3);
    std::cerr << turn.Current()->ToString() << std::endl;
    turn.Insert(player2);
    std::cerr << turn.Current()->ToString() << std::endl;
    turn.Insert(player1);
    std::cerr << turn.Current()->ToString() << std::endl;

    player2->SetDie(true);

    turn.Next();
    std::cerr << turn.Current()->ToString() << std::endl;
    EXPECT_EQ(turn.Current()->GetMoney(), 30000u);
}

TEST(TurnTests, ForEach)
{
    Turn turn;

    Player::Ptr player1 = std::make_unique<RandomPlayer>();
    Player::Ptr player2 = std::make_unique<RandomPlayer>();
    Player::Ptr player3 = std::make_unique<RandomPlayer>();

    player2->SetDie(true);

    turn.Insert(player1);
    turn.Insert(player2);
    turn.Insert(player3);

    std::size_t counter = 0;
    turn.ForEach([&counter](Player* player) { ++counter; });

    EXPECT_EQ(counter, 2u);
}

TEST(TurnTests, ForEachAll)
{
    Turn turn;

    Player::Ptr player1 = std::make_unique<RandomPlayer>();
    Player::Ptr player2 = std::make_unique<RandomPlayer>();
    Player::Ptr player3 = std::make_unique<RandomPlayer>();

    player2->SetDie(true);

    turn.Insert(player1);
    turn.Insert(player2);
    turn.Insert(player3);

    std::size_t counter = 0;
    turn.ForEachAll([&counter](Player* player) { ++counter; });

    EXPECT_EQ(counter, 3u);
}
