// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/Betting/FoldTask.h>

namespace Poker
{
TaskStatus FoldTask::Impl([[maybe_unused]] Player& player)
{
    // TODO: Impl this
    (void)money_;

    return TaskStatus::INVALID;
}

FoldTask::FoldTask(int money) : money_(money)
{
    // Do nothing
}
}  // namespace Poker
