// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/Betting/CallTask.h>

#include <Poker/Games/Game.h>

#include <stdexcept>

namespace Poker
{
TaskStatus CallTask::Impl(Player& player)
{
    const std::size_t& bet =
        player.GetGame().GetPreBetMoney() - player.GetPreBet();

    // 최소배팅금액, 내 잔고, 최대배팅금액 확인

    if (player.GetMoney() < player.GetGame().GetPreBetMoney())
    {
        throw std::logic_error("Not enough money");
    }

    player.SetMoney(player.GetMoney() - bet);
    player.GetGame().AddMoney(bet);

    player.SetPreBet(player.GetPreBet() + bet);

    player.GetGame().SetPreBetStat(TaskType::CALL);

    return TaskStatus::COMPLETE;
}

CallTask::CallTask()
{
    // Do nothing
}
}  // namespace Poker
