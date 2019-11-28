// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/Betting/AllInTask.h>

#include <Poker/Games/Game.h>

#include <stdexcept>

namespace Poker
{
TaskStatus AllInTask::Impl(Player& player)
{
    // 최소배팅금액, 내 잔고, 최대배팅금액 확인
    if (player.GetMoney() <
        player.GetGame().GetPreBetMoney() - player.GetPreBet())
    {
        throw std::logic_error("Not enough money");
    }

    player.GetGame().AddMoney(player.GetMoney());
    player.SetMoney(0);

    player.GetGame().SetPreBetMoney(player.GetPreBet() + player.GetMoney());
    player.SetPreBet(player.GetPreBet() + player.GetMoney());

    player.SetAllin(true);
    player.GetGame().ResetCallPlayer();
    player.GetGame().AddAllInPlayer();

    player.GetGame().SetPreBetStat(TaskType::ALLIN);

    return TaskStatus::COMPLETE;
}

AllInTask::AllInTask()
{
    // Do nothing
}
}  // namespace Poker