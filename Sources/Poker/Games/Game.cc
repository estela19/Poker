// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/Game.h>

#include <effolkronium/random.hpp>
#include <stdexcept>

using Random = effolkronium::random_static;

namespace Poker
{
Game::Game(GameConfig config) : config_(std::move(config))
{
    // Do nothing
}

void Game::BeginTurn()
{
}

void Game::OpenCard()
{
}

void Game::Betting()
{
}

void Game::EndTurn()
{
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

const std::set<Card>& Game::LeftCards() const
{
    return cards_;
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

void Game::fillCards()
{
    cards_.clear();

    for (int shape = 0; shape < static_cast<int>(CardShape::COUNT); ++shape)
    {
        for (int number = 0; number < static_cast<int>(CardNumber::COUNT);
             ++number)
        {
            cards_.emplace(static_cast<CardShape>(shape),
                           static_cast<CardNumber>(number));
        }
    }
}

Card Game::popCard()
{
    auto card = *Random::get(cards_);

    cards_.erase(card);
    return card;
}
}  // namespace Poker
