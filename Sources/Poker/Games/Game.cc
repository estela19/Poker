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
    if (status_ != GameStatus::ENDED)
    {
        throw std::logic_error("Game hasn't ended");
    }

    if (players_.size() <= 1)
    {
        throw std::logic_error("Player must be more than two");
    }

    fillCards();

    if (first_ == -1)
    {
        first_ = Random::get<int>(0, players_.size());
    }
    now_ = first_;

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

void Game::ProcessTurn()
{
    if (status_ != GameStatus::PLAYING)
    {
        throw std::logic_error("Game hasn't started");
    }

    Player* now = players_[now_].get();

    int cardsToGive = 1;
    if (now->GetDeck().Empty())
    {
        cardsToGive = config_.InitCard;
    }

    for (int i = 0; i < cardsToGive; ++i)
    {
        now->GetDeck().AddCard(popCard());
    }

    // TODO: 플레이어에게 행동 요구하기.
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
