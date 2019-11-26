// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_GAME_MANAGER_H
#define POKER_GAME_MANAGER_H

#include <Poker/Games/Game.h>
#include <Poker/Games/GameEnums.h>

namespace Poker
{
class GameManager final
{
 public:
    static void ProcessGame(Game& game, GameStatus status);
};
}  // namespace Poker

#endif  // POKER_GAME_MANAGER_H
