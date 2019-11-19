// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/Betting/RaiseTask.h>

#include <Poker/Games/Game.h>

#include <stdexcept>

namespace Poker
{
TaskStatus RaiseTask::Impl([[maybe_unused]] Player& player)
{
    const GameConfig& config = player.GetGame().GetConfig();
    const std::size_t& Bet = money_ + player.GetGame().GetpreBetMoney() - player.GetPreBet();

    // 최소배팅금액, 내 잔고, 최대배팅금액 확인
    if (config.MinBetMoney > money_)
    {
        throw std::logic_error("Betting more money");
    }

    if (config.MaxBetMoney < money_)
    {
        throw std::logic_error("Betting less money");
    }

    if (player.GetMoney() < Bet)
    {
        throw std::logic_error("Not enough money");
	}

    player.SetMoney(player.GetMoney() - Bet);
    player.GetGame().AddMoney(Bet);

    player.GetGame().SetpreBetMoney(player.GetGame().GetpreBetMoney() + money_);

    return TaskStatus::COMPLETE;
}

RaiseTask::RaiseTask(std::size_t money) : money_(money)
{
    // Do nothing
}
}  // namespace Poker
