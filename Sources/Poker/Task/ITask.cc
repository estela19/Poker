// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/ITask.h>

#include <iostream>

namespace Poker
{
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
}  // namespace Poker
