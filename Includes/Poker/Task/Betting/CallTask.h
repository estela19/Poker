// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_CALL_TASK_H
#define POKER_CALL_TASK_H

#include <Poker/Task/ITask.h>
#include <Poker/Task/TaskEnums.h>

namespace Poker
{
class CallTask : public ITask
{
 public:
    CallTask();

 private:
    TaskStatus Impl(Player& player) override;

};
}  // namespace Poker

#endif  // POKER_CALL_TASK_H
