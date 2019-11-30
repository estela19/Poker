// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Server/ConnectionPlayer.h>

#include <Poker/Task/Betting/AllInTask.h>
#include <Poker/Task/Betting/BetTask.h>
#include <Poker/Task/Betting/CallTask.h>
#include <Poker/Task/Betting/CheckTask.h>
#include <Poker/Task/Betting/FoldTask.h>
#include <Poker/Task/Betting/RaiseTask.h>

#include <Poker/Games/Game.h>

#include <sstream>

using namespace Poker;

ConnectionPlayer::ConnectionPlayer(Connection& _conn) : conn(_conn)
{
    _conn.player_ = this;

	name = _conn.Address();
}

void ConnectionPlayer::OnGameStarted()
{
    nlohmann::json j;
    addType(j, 1);
    addMyName(j);
    addOpName(j);

	conn.Write(j.dump());
}

std::size_t ConnectionPlayer::RequireOpenCard()
{
    nlohmann::json j;
    addType(j, 2);
    addMyCardList(j);
    addTotalMoney(j);

    conn.Write(j.dump());

    return std::stoi(conn.Read());
}

ITask::Ptr ConnectionPlayer::RequireBetting()
{
    nlohmann::json j;
    addType(j, 3);
    addMyCardList(j);
    addOpCardList(j);
    addMyMoney(j);
    addOpMoney(j);
    addTotalMoney(j);
    addValidBetMoney(j);

	conn.Write(j.dump());

    std::stringstream ss(conn.Read());

    std::string betType;
    ss >> betType;

    if (betType == "ALLIN")
    {
        return std::make_unique<AllInTask>();
    }
    else if (betType == "BET")
    {
        std::size_t money;
        ss >> money;

        return std::make_unique<BetTask>(money);
    }
    else if (betType == "CALL")
    {
        return std::make_unique<CallTask>();
    }
    else if (betType == "CHECK")
    {
        return std::make_unique<CheckTask>();
    }
    else if (betType == "FOLD")
    {
        return std::make_unique<FoldTask>();
    }
    else if (betType == "RAISE")
    {
        std::size_t money;
        ss >> money;

        return std::make_unique<RaiseTask>(money);
    }

    return nullptr;
}

void ConnectionPlayer::addType(nlohmann::json& j, int type) const
{
    j["Type"] = type;
}

void ConnectionPlayer::addMyName(nlohmann::json& j) const
{
    j["MyName"] = name;
}

void ConnectionPlayer::addOpName(nlohmann::json& j) const
{
    auto& op = static_cast<const ConnectionPlayer&>(GetGame().GetPlayer(!ID));

    j["OpName"] = op.name;
}

void ConnectionPlayer::addMyCardList(nlohmann::json& j) const
{
    std::vector<std::string> cards;

    for (std::size_t i = 0; i < GetDeck().Size(); ++i)
    {
        std::stringstream ss;

        auto& card = GetDeck().GetCard(i);
        ss << CardShapeStr[static_cast<std::size_t>(card.Shape())]
           << CardNumberStr[static_cast<std::size_t>(card.Number())];

        cards.emplace_back(ss.str());
    }

    j["MyCardList"] = cards;
}

void ConnectionPlayer::addOpCardList(nlohmann::json& j) const
{
    auto& op = static_cast<const ConnectionPlayer&>(GetGame().GetPlayer(!ID));
    std::vector<std::string> cards;

    for (std::size_t i = 0; i < op.GetDeck().Size(); ++i)
    {
        std::stringstream ss;

        auto& card = op.GetDeck().GetCard(i);
        if (card.IsOpen())
        {
            ss << CardShapeStr[static_cast<std::size_t>(card.Shape())]
               << CardNumberStr[static_cast<std::size_t>(card.Number())];
        }
        else
        {
            ss << "";
        }

        cards.emplace_back(ss.str());
    }

    j["OpCardList"] = cards;
}

void ConnectionPlayer::addMyMoney(nlohmann::json& j) const
{
    j["MyMoney"] = GetMoney();
}

void ConnectionPlayer::addOpMoney(nlohmann::json& j) const
{
    auto& op = static_cast<const ConnectionPlayer&>(GetGame().GetPlayer(!ID));
    j["OpMoney"] = op.GetMoney();
}

void ConnectionPlayer::addTotalMoney(nlohmann::json& j) const
{
    j["TotalMoney"] = GetGame().GetMoney();
}

void ConnectionPlayer::addValidBetMoney(nlohmann::json& j) const
{
    j["ValidBetMoney"] = GetGame().GetMaxRaisedMoney();
}

void ConnectionPlayer::addValid(nlohmann::json& j) const
{
    std::array<bool, 6> valids;
    std::fill(begin(valids), end(valids), false);

    for (const auto& task : GetGame().ValidTasks())
    {
        switch (task)
        {
            case TaskType::BET:
                valids[0] = true;
                break;

            case TaskType::RAISE:
                valids[1] = true;
                break;

            case TaskType::FOLD:
                valids[2] = true;
                break;

            case TaskType::CALL:
                valids[3] = true;
                break;

            case TaskType::CHECK:
                valids[4] = true;
                break;

            case TaskType::ALLIN:
                valids[5] = true;
                break;
        }
    }

    j["Valid"] = valids;
}

void ConnectionPlayer::addWinner(nlohmann::json& j) const
{
    if (GetGame().Winner != nullptr)
    {
        j["Winner"] =
            static_cast<const ConnectionPlayer*>(GetGame().Winner)->ID == ID;
    }
    else
    {
        j["Winner"] = false;
    }
}
