// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/Game.h>

#include <Poker/Games/GameManager.h>

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
    if (turn_.GetSize() == 0)
    {
        throw std::logic_error("No players inserted");
    }

    cards_.clear();
    fillCards();

    // Ä«µå ³ª´²Áà¾ßÇØ (¼¼Àå)
    for (std::size_t i = 0; i < turn_.GetSize(); ++i)
    {
        auto& nowDeck = turn_.Current()->GetDeck();

        if (nowDeck.Size() != 0)
        {
            throw std::logic_error("Already game started");
        }

        for (std::size_t j = 0; j < config_.InitCard; ++j)
        {
            nowDeck.AddCard(popCard());
        }
        turn_.Next();
    }

    if (config_.AutoPlay)
    {
        GameManager::ProcessGame(*this, GameStatus::OPEN_CARDS);
    }
}

void Game::OpenCard()
{
    // Ä«µå ÇÏ³ª¸¦ µÚÁý¾î¾ßÇØ

    for (std::size_t i = 0; i < turn_.GetSize(); ++i)
    {
        auto& nowDeck = turn_.Current()->GetDeck();
        std::size_t openCard = turn_.Current()->RequireOpenCard();

        if (openCard >= nowDeck.Size())
        {
            throw std::logic_error("Invalid card id");
        }

        nowDeck.GetCard(openCard).SetOpen(true);
        turn_.Next();
    }
}

void Game::Betting()
{
    auto& nowDeck = turn_.Current()->GetDeck();

    if (config_.AutoPlay && nowDeck.Size() == config_.MaxCard)
    {
        GameManager::ProcessGame(*this, GameStatus::END_TURN);
    }

    nowDeck.AddCard(popCard());
    if (nowDeck.Size() != config_.MaxCard)
    {
        nowDeck.GetCard(nowDeck.Size() - 1).SetOpen(true);
    }
}

void Game::EndTurn()
{
    // TODO : ½ÂÆÐÆÇÁ¤
    std::size_t winner = 0;

    if (winner >= turn_.GetSize())
    {
        throw std::logic_error("Invalid winner id");
    }

    // ÆÇµ· ½ÂÀÚ¿¡°Ô ÁÜ
    GetPlayer(winner).SetMoney(GetMoney() + GetPlayer(winner).GetMoney());

    // player isDie reset
    for (std::size_t i = 0; i < turn_.GetSize(); ++i)
    {
        turn_.Current()->SetDie(false);
    }

    // preBetMoney reset
    SetpreBetMoney(0);

    //(player)preBet reset
    turn_.ForEach([&](Player* player) { player->SetPreBet(0); });
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

void Game::ChoiceBetting(BettingStatus betting)
{
    // TODO : implement choice betting
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

const GameConfig& Game::GetConfig() const
{
    return config_;
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

std::size_t Game::GetpreBetMoney() const
{
    return preBetMoney_;
}

void Game::SetpreBetMoney(std::size_t money)
{
    preBetMoney_ = money;
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
