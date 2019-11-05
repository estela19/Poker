// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/Betting/RaiseTask.h>

namespace Poker
{
TaskStatus RaiseTask::Impl()
{
    // TODO: Impl this

    return TaskStatus::INVALID;
}

RaiseTask::RaiseTask(int money) : money_(money)
{
    // Do nothing
}
}  // namespace Poker
