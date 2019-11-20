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

    // 카드 나눠줘야해 (세장)
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
    // 카드 하나를 뒤집어야해

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

void Game::PreBetting()
{
    // 카드 나눠주기
    turn_.ForEach([&](Player* player) {
        auto& nowDeck = player->GetDeck();
        nowDeck.AddCard(popCard());
        nowDeck.GetCard(nowDeck.Size() - 1).SetOpen(true);
    });

    // TODO : 선 정하기

    if (config_.AutoPlay)
    {
        GameManager::ProcessGame(*this, GameStatus::BETTING);
    }
}

void Game::Betting()
{
    ITask::Ptr task = turn_.Current()->RequireBetting();
    Process(task.get());
        // card가 maxcard개면 endturn
        auto& nowDeck = turn_.Current()->GetDeck();
    if (config_.AutoPlay && nowDeck.Size() == config_.MaxCard &&
        turn_.GetSize() == 1)
    {
        GameManager::ProcessGame(*this, GameStatus::END_TURN);
    }
}

void Game::EndTurn()
{
    // TODO : 승패판정 (player가 한명만 남았을때도 고려)
    std::size_t winner = 0;

    if (winner >= turn_.GetSize())
    {
        throw std::logic_error("Invalid winner id");
    }

    // 판돈 승자에게 줌
    GetPlayer(winner).SetMoney(GetMoney() + GetPlayer(winner).GetMoney());

    // player isDie reset
    for (std::size_t i = 0; i < turn_.GetSize(); ++i)
    {
        turn_.Current()->SetDie(false);
    }

    // preBetMoney reset
    SetPreBetMoney(0);

    //(player)preBet reset
    turn_.ForEach([&](Player* player) { player->SetPreBet(0); });
}

void Game::Process(ITask* task)
{
    Player* player = turn_.Current();
    if (player->IsDie())
    {
        throw std::logic_error("Invalid player id");
    }

    task->SetPlayer(player);
    task->Run();
}

bool Game::ChoiceBetting(TaskType betting)
{
    switch (preBetStat_)
    {
        case TaskType::INVALID:
            switch (betting)
            {
                case Poker::TaskType::BET:
                case Poker::TaskType::CHECK:
                case Poker::TaskType::FOLD:
                    return true;

                default:
                    return false;
            }

        case TaskType::BET:
            switch (betting)
            {
                case Poker::TaskType::RAISE:
                case Poker::TaskType::CALL:
                case Poker::TaskType::FOLD:
                    return true;

                default:
                    return false;
            }

        case TaskType::CHECK:
            switch (betting)
            {
                case Poker::TaskType::RAISE:
                case Poker::TaskType::CHECK:
                case Poker::TaskType::FOLD:
                    return true;

                default:
                    return false;
            }

        case TaskType::RAISE:
            switch (betting)
            {
                case Poker::TaskType::RAISE:
                case Poker::TaskType::CALL:
                case Poker::TaskType::FOLD:
                    return true;

                default:
                    return false;
            }

        default:
            throw std::logic_error("Can't choice Action");
    }
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

std::size_t Game::GetPreBetMoney() const
{
    return preBetMoney_;
}

void Game::SetPreBetMoney(std::size_t money)
{
    preBetMoney_ = money;
}

void Game::SetPreBetStat(TaskType task)
{
    preBetStat_ = task;
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
