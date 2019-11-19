// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/Betting/CallTask.h>

namespace Poker
{
TaskStatus CallTask::Impl([[maybe_unused]] Player& player)
{
    // TODO: Impl this
    (void)money_;

    return TaskStatus::INVALID;
}

CallTask::CallTask(int money) : money_(money)
{
    // Do nothing
}
}  // namespace Poker
