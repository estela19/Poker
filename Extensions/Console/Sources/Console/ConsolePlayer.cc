// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Console/ConsolePlayer.h>

#include <Poker/Games/Game.h>
#include <Poker/Task/Betting/BetTask.h>
#include <Poker/Task/Betting/CallTask.h>
#include <Poker/Task/Betting/CheckTask.h>
#include <Poker/Task/Betting/FoldTask.h>
#include <Poker/Task/Betting/RaiseTask.h>

#include <iostream>
#include <sstream>

using namespace Poker;

ConsolePlayer::ConsolePlayer(std::size_t playerId) : playerId_(playerId)
{
    // Do nothing
}

std::size_t ConsolePlayer::RequireOpenCard() const
{
    std::size_t bet = 4;

    do
    {
        std::cout << "[카드 목록]" << std::endl;
        PrintCardList();

        std::cout << "열 카드의 숫자 입력: ";
        std::cin >> bet;
    } while (bet >= 3);

    return bet;
}

ITask::Ptr ConsolePlayer::RequireBetting() const
{
    std::vector<TaskType> valid = GetGame().ValidTasks();
    std::size_t choice = valid.size();

    do
    {
        std::cout << "[행동 목록]" << std::endl;

        for (std::size_t choiceIdx = 0; choiceIdx < valid.size(); ++choiceIdx)
        {
            std::cout << choiceIdx << ". "
                      << TaskTypeStr[static_cast<std::size_t>(valid[choiceIdx])]
                      << std::endl;
        }

        std::cout << "할 행동의 숫자 입력: ";
        std::cin >> choice;
    } while (!(choice < valid.size()));

    if (valid[choice] == TaskType::BET)
    {
        std::size_t money = 0;
        const std::size_t minMoney = GetGame().GetConfig().MinBetMoney;

        do
        {
            std::cout << "베팅할 금액 입력: ";
            std::cin >> money;
        } while (!(money <= GetMoney() && money >= minMoney));

        return std::make_unique<BetTask>(money);
    }
    else if (valid[choice] == TaskType::CALL)
    {
        return std::make_unique<CallTask>();
    }
    else if (valid[choice] == TaskType::CHECK)
    {
        return std::make_unique<CheckTask>();
    }
    else if (valid[choice] == TaskType::FOLD)
    {
        return std::make_unique<FoldTask>();
    }
    else if (valid[choice] == TaskType::RAISE)
    {
        std::size_t money = 0;

        do
        {
            std::cout << "레이즈할 금액 입력: ";
            std::cin >> money;
        } while (money <= GetMoney() && money >= GetGame().GetPreBetMoney());

        return std::make_unique<RaiseTask>(money);
    }

    return nullptr;
}

std::string ConsolePlayer::ToString() const
{
    std::stringstream ss;
    ss << "[플레이어 " << playerId_ << "]" << std::endl;
    ss << "잔고: " << GetMoney() << std::endl << std::endl;

    ss << PlayerCardListToString();

	return ss.str();
}

std::string ConsolePlayer::PlayerCardListToString() const
{
    std::stringstream ss;

    for (std::size_t cardIdx = 0; cardIdx < GetDeck().Size(); ++cardIdx)
    {
        ss << cardIdx << ". ";

        auto& card = GetDeck().GetCard(cardIdx);
        ss << CardShapeStr[static_cast<std::size_t>(card.Shape())]
                  << CardNumberStr[static_cast<std::size_t>(card.Number())]
                  << std::endl;
    }

	return ss.str();
}

void ConsolePlayer::PrintCardList() const
{
    std::cout << PlayerCardListToString();
}
