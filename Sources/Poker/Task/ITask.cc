// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/ITask.h>

namespace Poker
{
ITask::ITask(TaskType type) : type_(type)
{
    // Do nothing
}

void ITask::SetPlayer(const Player::Ptr& player)
{
    player_ = player.get();
}

const Player& ITask::GetPlayer() const
{
    return *player_;
}

TaskStatus ITask::Run()
{
    return Impl(*player_);
}

TaskType ITask::GetType() const
{
    return type_;
}
}  // namespace Poker
