// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/GameManager.h>

namespace Poker
{
void GameManager::ProcessGame(Game& game, GameStatus status)
{
    switch (status)
    {
        case GameStatus::BEGIN_TURN:
            game.BeginTurn();
            break;

        case GameStatus::OPEN_CARDS:
            game.OpenCard();
            break;

        case GameStatus::BETTING:
            game.Betting();
            break;

        case GameStatus::END_TURN:
            game.EndTurn();
            break;
    }

    game.status_ = status;
}
}  // namespace Poker
