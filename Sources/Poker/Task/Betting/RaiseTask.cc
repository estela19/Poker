// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/Betting/RaiseTask.h>

#include <Poker/Games/Game.h>

#include <stdexcept>

namespace Poker
{
TaskStatus RaiseTask::Impl(Player& player)
{
    const GameConfig& config = player.GetGame().GetConfig();
    const std::size_t& bet =
        money_ + player.GetGame().GetPreBetMoney() - player.GetPreBet();

    // �ּҹ��ñݾ�, �� �ܰ�, �ִ���ñݾ� Ȯ��
    if (config.MinBetMoney > money_)
    {
        throw std::logic_error("Betting more money");
    }

    if (config.MaxBetMoney < money_)
    {
        throw std::logic_error("Betting less money");
    }

    if (player.GetMoney() < bet)
    {
        throw std::logic_error("Not enough money");
    }

    player.SetMoney(player.GetMoney() - bet);
    player.GetGame().AddMoney(bet);

    player.GetGame().SetPreBetMoney(player.GetGame().GetPreBetMoney() + money_);
    player.SetPreBet(player.GetPreBet() + bet);

	player.GetGame().ResetCallPlayer();

    player.GetGame().SetPreBetStat(TaskType::RAISE);

    return TaskStatus::COMPLETE;
}

RaiseTask::RaiseTask(std::size_t money) : money_(money)
{
    // Do nothing
}
}  // namespace Poker
