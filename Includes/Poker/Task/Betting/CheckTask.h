// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_CHECK_TASK_H
#define POKER_CHECK_TASK_H

#include <Poker/Task/ITask.h>
#include <Poker/Task/TaskEnums.h>

namespace Poker
{
class CheckTask : public ITask
{
 public:
    CheckTask();

 private:
    TaskStatus Impl(Player& player) override;

};
}  // namespace Poker

#endif  // POKER_CHECK_TASK_H
