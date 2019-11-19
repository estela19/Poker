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
    RaiseTask(std::size_t money);

 private:
    TaskStatus Impl(Player& player) override;

 private:
    std::size_t money_;
};
}  // namespace Poker

#endif  // POKER_RAISE_TASK_H
