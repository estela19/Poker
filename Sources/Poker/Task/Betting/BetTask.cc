// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/Betting/BetTask.h>

namespace Poker
{
TaskStatus BetTask::Impl([[maybe_unused]] Player& player)
{
    // TODO: Impl this
    (void)money_;

    return TaskStatus::INVALID;
}

BetTask::BetTask(int money) : money_(money)
{
    // Do nothing
}
}  // namespace Poker
