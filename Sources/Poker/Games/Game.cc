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
    // ī�� ��������� (����)
    for (int i = 0; i < turn_.GetSize(); ++i)
    {
        for (int j = 0; j < config_.InitCard; ++j)
        {
            turn_.Current()->GetDeck().AddCard(popCard());
        }
        turn_.Next();
    }
}

void Game::OpenCard()
{
    // ī�� �ϳ��� ���������
    for (int i = 0; i < turn_.GetSize(); ++i)
    {
        turn_.Current()
            ->GetDeck()
            .GetCard(turn_.Current()->RequireOpenCard())
            .SetOpen(true);
        turn_.Next();
    }
}

void Game::Betting()
{
    // ī�� �ϳ��� ���� �����
    turn_.Current()->GetDeck().AddCard(popCard());
    // TODO : ���� ���ؾ���
    // TODO : ������ �ؾ���
}

void Game::EndTurn()
{
    // ī��set reset
    cards_.clear();
    fillCards();

    // TODO : ��������
    std::size_t winner;

    // �ǵ� ���ڿ��� ��
    GetPlayer(winner).SetMoney(GetMoney() + GetPlayer(winner).GetMoney());

    // player isDie reset
    for (int i = 0; i < turn_.GetSize(); ++i)
    {
        turn_.Current()->SetDie(false);
    }
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

std::size_t Game::GetMoney() const
{
    return money_;
}

void Game::AddMoney(std::size_t money)
{
    money_ += money;
}

void Game::ResetMoney()
{
    money_ = 0;
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
