// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_FOLD_TASK_H
#define POKER_FOLD_TASK_H

#include <Poker/Task/ITask.h>
#include <Poker/Task/TaskEnums.h>

namespace Poker
{
class FoldTask : public ITask
{
 public:
    FoldTask();

 private:
    TaskStatus Impl(Player& player) override;
};
}  // namespace Poker

#endif  // POKER_FOLD_TASK_H
