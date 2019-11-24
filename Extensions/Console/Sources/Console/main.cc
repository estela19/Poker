// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <iostream>

#include <Console/ConsolePlayer.h>

#include <Poker/Games/Game.h>
#include <Poker/Games/GameManager.h>

using namespace Poker;

int main(int argc, char** argv)
{
    GameConfig config = LoadConfig("./config.json");
    Game game{ config };

    std::size_t playerCount = 0;

    do
    {
        std::cout << "플레이어의 수를 입력: ";
        std::cin >> playerCount;
    } while (playerCount < 1);

    for (std::size_t i = 0; i < playerCount; ++i)
    {
        game.AddPlayer<ConsolePlayer>(i);
    }

    while (game.GetPlayerCount() > 1)
    {
        GameManager::ProcessGame(game, GameStatus::BEGIN_TURN);
    }
}
