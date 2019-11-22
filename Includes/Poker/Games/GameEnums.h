// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_GAME_ENUMS_H
#define POKER_GAME_ENUMS_H

namespace Poker
{
enum class GameStatus
{
    INVALID,
    BEGIN_TURN,
    OPEN_CARDS,
    PRE_BETTING,
    BETTING,
    END_TURN
};
}

#endif  // POKER_GAME_ENUMS_H