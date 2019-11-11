// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_RAISE_TASK_H
#define POKER_RAISE_TASK_H

#include <Poker/Task/ITask.h>
#include <Poker/Task/TaskEnums.h>

namespace Poker
{
class RaiseTask : public ITask
{
 public:
    RaiseTask(int money);

 private:
    TaskStatus Impl() override;

 private:
    int money_;
};
}  // namespace Poker

#endif  // POKER_RAISE_TASK_H
