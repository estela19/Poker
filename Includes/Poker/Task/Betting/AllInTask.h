// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_ALLIN_TASK_H
#define POKER_ALLIN_TASK_H

#include <Poker/Task/ITask.h>
#include <Poker/Task/TaskEnums.h>

namespace Poker
{
class AllInTask : public ITask
{
 public:
    AllInTask();

 private:
    TaskStatus Impl(Player& player) override;
};
}  // namespace Poker
#endif  // POKER_ALLIN_TASK_H
