// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_GAME_H
#define POKER_GAME_H

#include <Poker/Games/GameConfig.h>
#include <Poker/Games/GameEnums.h>
#include <Poker/Games/Turn.h>
#include <Poker/Players/Player.h>
#include <Poker/Task/ITask.h>
#include <Poker/Task/TaskEnums.h>

#include <optional>
#include <set>
#include <utility>
#include <vector>

namespace Poker
{
class Game final
{
 public:
    Game(GameConfig config);

    template <typename PlayerT, typename... Args>
    void AddPlayer(Args&&... args)
    {
        players_.emplace_back(std::make_unique<PlayerT>(std::move(args)...));
        players_.back()->SetMoney(config_.InitMoney);
        players_.back()->SetGame(this);

        turn_.Insert(players_.back());
    }

    void BeginTurn();
    void OpenCard();
    void PreBetting();
    void Betting();
    void EndTurn();

    GameStatus GetStatus() const;

    void Process(ITask* task);

    bool ChoiceBetting(TaskType betting) const;
    std::vector<TaskType> ValidTasks() const;

    const std::set<Card>& LeftCards() const;

    Player& GetPlayer(std::size_t index);
    const Player& GetPlayer(std::size_t index) const;
    std::size_t GetPlayerCount() const;

    const GameConfig& GetConfig() const;

    Turn& GetTurn();

    std::size_t GetMoney() const;
    void AddMoney(std::size_t money);
    void ResetMoney();

    std::size_t GetPreBetMoney() const;
    void SetPreBetMoney(std::size_t money);

    void SetPreBetStat(TaskType task);

    void KillPlayer(Player* player);

	void AddAllInPlayer();

	std::size_t GetCallPlayer();
	void AddCallPlayer();
    void ResetCallPlayer();

 private:
    void fillCards();
    Card popCard();

 private:
    GameConfig config_;
    GameStatus status_ = GameStatus::INVALID;

    TaskType preBetStat_ = TaskType::INVALID;
    std::size_t preBetMoney_ = 0;

    Turn turn_;
    std::vector<Player::Ptr> players_;
    std::size_t livePlayerCount_ = 0;
    std::size_t allInPlayerCount_ = 0;
    std::size_t callPlayerCount_ = 0;
    std::set<Card> cards_;
    std::size_t money_ = 0;

    friend class GameManager;
};
}  // namespace Poker

#endif  // POKER_GAME_H
