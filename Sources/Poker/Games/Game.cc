// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/Game.h>

#include <stdexcept>

namespace Poker
{
void Game::BeginTurn()
{
    if (status_ != GameStatus::ENDED)
    {
        throw std::logic_error("Game hasn't ended");
    }

    status_ = GameStatus::PLAYING;
}

void Game::EndTurn()
{
    if (status_ != GameStatus::PLAYING)
    {
        throw std::logic_error("Game hasn't started");
    }

    // TODO: 승패 판정 코드

    status_ = GameStatus::ENDED;
}

void Game::Process(std::size_t id, ITask&& task)
{
    if (id >= players_.size())
    {
        throw std::logic_error("Invalid player id");
    }

    task.SetPlayer(players_[id]);
    task.Run();
}

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
