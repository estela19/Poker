// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Players/RandomPlayer.h>
#include <Poker/Task/Betting/FoldTask.h>

#include <effolkronium/random.hpp>
#include <sstream>

namespace Poker
{
std::size_t RandomPlayer::RequireOpenCard() const
{
    using Random = effolkronium::random_static;

    return Random::get<std::size_t>(0u, GetDeck().Size() - 1);
}

ITask::Ptr RandomPlayer::RequireBetting() const 
{ 
	return std::make_unique<FoldTask>();
}

std::string RandomPlayer::ToString() const
{
    std::stringstream ss;

    ss << "[RandomPlayer] Money(" << GetMoney() << ") Dead?(" << std::boolalpha
       << IsDie() << ")";

    return ss.str();
}
}  // namespace Poker
