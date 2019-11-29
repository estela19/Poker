// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Server/ConnectionPlayer.h>

using namespace Poker;

ConnectionPlayer::ConnectionPlayer(Connection& _conn)
    : conn(_conn)
{
    _conn.player_ = this;
}

std::size_t ConnectionPlayer::RequireOpenCard() const
{

	return 0;
}

ITask::Ptr ConnectionPlayer::RequireBetting() const
{

	return nullptr;
}
