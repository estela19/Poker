// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_BET_TASK_H
#define POKER_BET_TASK_H

#include <Poker/Task/ITask.h>
#include <Poker/Task/TaskEnums.h>

namespace Poker
{
class BetTask : public ITask
{
 public:
    BetTask(std::size_t money);

 private:
    TaskStatus Impl(Player& player) override;

 private:
    std::size_t money_;
};
}  // namespace Poker

#endif  // POKER_BET_TASK_H
