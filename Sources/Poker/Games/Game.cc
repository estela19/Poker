// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/Game.h>

namespace Poker
{
Player& Game::GetPlayer(std::size_t index)
{
    return const_cast<Player&>(
        static_cast<const Game&>(*this).GetPlayer(index));
}

const Player& Game::GetPlayer(std::size_t index) const
{
    return *players_[index];
}

std::size_t Game::GetPlayerCount() const
{
    return players_.size();
}
}  // namespace Poker
