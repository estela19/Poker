// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Server/ConnectionPlayer.h>

#include <Poker/Task/Betting/AllInTask.h>
#include <Poker/Task/Betting/BetTask.h>
#include <Poker/Task/Betting/CallTask.h>
#include <Poker/Task/Betting/CheckTask.h>
#include <Poker/Task/Betting/FoldTask.h>
#include <Poker/Task/Betting/RaiseTask.h>

#include <sstream>

using namespace Poker;

ConnectionPlayer::ConnectionPlayer(Connection& _conn) : conn(_conn)
{
    _conn.player_ = this;
}

std::size_t ConnectionPlayer::RequireOpenCard() const
{
    return std::stoi(conn.GetFuture().get());
}

ITask::Ptr ConnectionPlayer::RequireBetting() const
{
    std::stringstream ss(conn.GetFuture().get());

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
