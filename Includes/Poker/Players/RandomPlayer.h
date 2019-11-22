// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_RANDOM_PLAYER_H
#define POKER_RANDOM_PLAYER_H

#include <Poker/Players/Player.h>

#include <Poker/Task/TaskEnums.h>

namespace Poker
{
class RandomPlayer : public Player
{
 public:
    std::size_t RequireOpenCard() const override;

    ITask::Ptr RequireBetting() const override;

    std::string ToString() const override;
};
}  // namespace Poker

#endif  // POKER_RANDOM_PLAYER_H