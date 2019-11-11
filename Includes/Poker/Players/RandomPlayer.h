// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_RANDOM_PLAYER_H
#define POKER_RANDOM_PLAYER_H

#include <Poker/Players/Player.h>

namespace Poker
{
class RandomPlayer : public Player
{
 public:
    std::size_t RequireOpenCard() const override;

    std::string ToString() const override;
};
}  // namespace Poker

#endif  // POKER_RANDOM_PLAYER_H