// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/Betting/CheckTask.h>

#include <Poker/Games/Game.h>

namespace Poker
{
TaskStatus CheckTask::Impl(Player& player)
{
    auto& game = player.GetGame();
    if (player.GetGame().GetCallPlayer() != 0)
    {
        game.AddCallPlayer();     
    }

    game.SetPreBetStat(TaskType::CHECK);

    return TaskStatus::COMPLETE;
}

CheckTask::CheckTask()
{
    // Do nothing
}
}  // namespace Poker
