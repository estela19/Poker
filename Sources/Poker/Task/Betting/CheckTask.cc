// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/Betting/CheckTask.h>

namespace Poker
{
TaskStatus CheckTask::Impl([[maybe_unused]] Player& player)
{
    // TODO: Impl this
    (void)money_;

    return TaskStatus::INVALID;
}

CheckTask::CheckTask(int money) : money_(money)
{
    // Do nothing
}
}  // namespace Poker
