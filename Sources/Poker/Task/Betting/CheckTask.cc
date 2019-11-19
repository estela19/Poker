// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/Betting/CheckTask.h>

namespace Poker
{
TaskStatus CheckTask::Impl([[maybe_unused]] Player& player)
{
    return TaskStatus::COMPLETE;
}

CheckTask::CheckTask()
{
    // Do nothing
}
}  // namespace Poker
