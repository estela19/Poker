// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/Betting/BetTask.h>

#include <Poker/Games/Game.h>

#include <stdexcept>

namespace Poker
{
TaskStatus BetTask::Impl([[maybe_unused]] Player& player)
{
    const GameConfig& config = player.GetGame().GetConfig();
    

    // 최소배팅금액, 내 잔고, 최대배팅금액 확인
    if (config.MinBetMoney > money_)
    {
        throw std::logic_error("Betting more money");
    }

    if (config.MaxBetMoney < money_)
    {
        throw std::logic_error("Betting less money");
    }

    if (player.GetMoney() < money_)
    {
        throw std::logic_error("Not enough money");
    }

    player.SetMoney(player.GetMoney() - money_);
    player.GetGame().AddMoney(money_);

    player.GetGame().SetpreBetMoney(money_);
    player.SetPreBet(money_);

    return TaskStatus::COMPLETE;
}

BetTask::BetTask(std::size_t money) : money_(money)
{
    // Do nothing
}
}  // namespace Poker
