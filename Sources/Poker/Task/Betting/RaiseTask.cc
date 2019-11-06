// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/Betting/RaiseTask.h>

namespace Poker
{
TaskStatus RaiseTask::Impl([[maybe_unused]]Player& player)
{
    // TODO: Impl this
    (void)money_;

    return TaskStatus::INVALID;
}

RaiseTask::RaiseTask(int money) : money_(money)
{
    // Do nothing
}
}  // namespace Poker
