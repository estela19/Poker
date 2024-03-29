// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/Game.h>

#include <Poker/Games/GameManager.h>

#include <Poker/Cards/CardDecks.h>

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
    turn_.ForEach([&](Player* player) {
        auto& nowDeck = turn_.Current()->GetDeck();

        if (nowDeck.Size() != 0)
        {
            throw std::logic_error("Already game started");
        }

        for (std::size_t j = 0; j < config_.InitCard; ++j)
        {
            nowDeck.AddCard(popCard());
        }
    });

    livePlayerCount_ = players_.size();

    if (config_.AutoPlay)
    {
        GameManager::ProcessGame(*this, GameStatus::OPEN_CARDS);
    }
}

void Game::OpenCard()
{
    // 카드 하나를 뒤집어야해

    turn_.ForEach([&](Player* player) {
        auto& nowDeck = player->GetDeck();
        std::size_t openCard = player->RequireOpenCard();

        if (openCard >= nowDeck.Size())
        {
            throw std::logic_error("Invalid card id");
        }

        nowDeck.GetCard(openCard).SetOpen(true);
    });

    if (config_.AutoPlay)
    {
        GameManager::ProcessGame(*this, GameStatus::PRE_BETTING);
    }
}

void Game::PreBetting()
{
    if (preBetStat_ != TaskType::INVALID)
    {
        callPlayerCount_ = allInPlayerCount_;
    }
    else
    {
        ResetCallPlayer();
    }

    turn_.Current()->SuccessFlag();
    maxRaisedMoney_ = 0;
    preBetStat_ = TaskType::INVALID;

    // preBetMoney reset
    SetPreBetMoney(0);

    // 카드 나눠주기
    turn_.ForEach([&](Player* player) {
        player->SetPreBet(0);

        auto& nowDeck = player->GetDeck();
        nowDeck.AddCard(popCard());
        nowDeck.GetCard(nowDeck.Size() - 1).SetOpen(true);
    });

    // 받은 패가 가장 좋은 사람을 선 플레이어로 결정
    std::vector<std::pair<std::size_t, Player*>> deckRank;
    turn_.ForEach([&](Player* player) {
        deckRank.push_back(
            std::make_pair(static_cast<std::size_t>(
                               CardDecks::Get(player->GetDeck().GetCardSet())),
                           player));
    });

    const Player* first =
        std::max_element(deckRank.begin(), deckRank.end())->second;

    // 선 플레이어를 turn의 now로 설정
    while (turn_.Current() != first)
    {
        turn_.Next();
    }

    if (config_.AutoPlay)
    {
        GameManager::ProcessGame(*this, GameStatus::BETTING);
    }
}

void Game::Betting()
{
    if (!(turn_.Current()->IsAllin()))
    {
        ITask::Ptr task = turn_.Current()->RequireBetting();
        Process(task.get());
        turn_.Current()->OnBettingDone();
    }

    // card가 maxcard개면 endturn
    auto& nowDeck = turn_.Current()->GetDeck();
    if (config_.AutoPlay &&
        (nowDeck.Size() == config_.MaxCard || livePlayerCount_ == 1))
    {
        GameManager::ProcessGame(*this, GameStatus::END_TURN);
    }
    else if (config_.AutoPlay && (allInPlayerCount_ == livePlayerCount_ ||
                                  callPlayerCount_ == livePlayerCount_))
    {
        GameManager::ProcessGame(*this, GameStatus::PRE_BETTING);
    }
    else if (config_.AutoPlay)
    {
        turn_.Next();
        GameManager::ProcessGame(*this, GameStatus::BETTING);
    }
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

void Game::EndTurn()
{
    Player* winner;

    // 모든 플레이어가 fold를 선언해서 한명만 남았을 경우
    if (livePlayerCount_ == 1)
    {
        do
        {
            turn_.Next();
        } while (turn_.Current()->IsDie());
        winner = turn_.Current();
    }

    else
    {  // pair의 첫번째 인자 : 가지고 있는 패(enum의 int형), 두번째 인자 : 그
       // 패의 주인
        std::vector<std::pair<std::size_t, Player*>> deckRank;
        turn_.ForEach([&](Player* player) {
            deckRank.push_back(std::make_pair(
                static_cast<std::size_t>(
                    CardDecks::Get(player->GetDeck().GetCardSet())),
                player));
        });

        //패의 우선순위가 가장높은(enum의 int형이 가장 작은) 사람의 포인터를
        // winner에 전달
        winner = std::max_element(deckRank.begin(), deckRank.end())->second;
    }

    // 판돈 승자에게 줌
    winner->SetMoney(GetMoney() + winner->GetMoney());

    // player isDie reset
    turn_.ForEachAll([&](Player* player) {
        player->SetDie(false);
        player->SetAllin(false);
        player->SetPreBet(0);
        player->GetDeck().Clear();
    });

    // preBetMoney reset
    SetPreBetMoney(0);

    turn_.ForEach([&](Player* player) {
        if (player->GetMoney() == 0)
        {
            turn_.Pop();
        }
    });

    for (auto it = players_.begin(); it != players_.end();)
    {
        if ((*it)->GetMoney() == 0)
        {
            (*it).reset();
            it = players_.erase(it);
        }
        else
        {
            ++it;
        }
    }

    turn_.Current()->SuccessFlag();
}

GameStatus Game::GetStatus() const
{
    return status_;
}

bool Game::ChoiceBetting(TaskType betting) const
{
    switch (preBetStat_)
    {
        case TaskType::INVALID:
            switch (betting)
            {
                case TaskType::BET:
                case TaskType::CHECK:
                case TaskType::FOLD:
                case TaskType::ALLIN:
                    return true;

                default:
                    return false;
            }

        case TaskType::BET:
            switch (betting)
            {
                case TaskType::RAISE:
                case TaskType::CALL:
                case TaskType::FOLD:
                case TaskType::ALLIN:
                    return true;

                default:
                    return false;
            }

        case TaskType::CHECK:
            switch (betting)
            {
                case TaskType::RAISE:
                case TaskType::CHECK:
                case TaskType::FOLD:
                case TaskType::ALLIN:
                    return true;

                default:
                    return false;
            }

        case TaskType::RAISE:
            switch (betting)
            {
                case TaskType::RAISE:
                case TaskType::CALL:
                case TaskType::FOLD:
                case TaskType::ALLIN:
                    return true;

                default:
                    return false;
            }

        case TaskType::ALLIN:
            switch (betting)
            {
                case Poker::TaskType::RAISE:
                case Poker::TaskType::CALL:
                case Poker::TaskType::FOLD:
                case Poker::TaskType::ALLIN:
                    return true;

                default:
                    return false;
            }

        default:
            throw std::logic_error("Can't choice Action");
    }
}

std::vector<TaskType> Game::ValidTasks() const
{
    std::vector<TaskType> ret;

    for (int i = 1; i < static_cast<int>(TaskType::COUNT); ++i)
    {
        if (ChoiceBetting(static_cast<TaskType>(i)))
        {
            ret.emplace_back(static_cast<TaskType>(i));
        }
    }

    return ret;
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

Turn& Game::GetTurn()
{
    return turn_;
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

void Game::KillPlayer(Player* player)
{
    --livePlayerCount_;
    player->SetDie(true);
}

std::size_t Game::GetCallPlayer() const
{
    return callPlayerCount_;
}

void Game::AddCallPlayer()
{
    callPlayerCount_++;
}

void Game::ResetCallPlayer()
{
    callPlayerCount_ = allInPlayerCount_ + 1;
}

void Game::AddAllInPlayer()
{
    allInPlayerCount_++;
}

std::size_t Game::GetMaxRaisedMoney() const
{
    return maxRaisedMoney_;
}

void Game::SetMaxRaisedMoney(std::size_t money)
{
    maxRaisedMoney_ = money;
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
