// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Server/ConnectionPlayer.h>

using namespace Poker;

ConnectionPlayer::ConnectionPlayer(Connection& conn)
    : conn_(conn)
{
	// Do nothing
}

std::size_t ConnectionPlayer::RequireOpenCard() const
{
    conn_.Write("Require Open Card\n");

	return 0;
}

ITask::Ptr ConnectionPlayer::RequireBetting() const
{
    conn_.Write("Require Betting\n");

	return nullptr;
}
