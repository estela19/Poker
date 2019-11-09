// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_GAME_H
#define POKER_GAME_H

#include <Poker/Games/GameConfig.h>
#include <Poker/Games/GameEnums.h>
#include <Poker/Games/Player.h>
#include <Poker/Games/Turn.h>
#include <Poker/Task/ITask.h>

#include <set>
#include <vector>
#include <optional>

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
    }

    void BeginTurn();
    void EndTurn();
    void Process(std::size_t id, ITask&& task);
    void ProcessTurn();

    const std::set<Card>& LeftCards() const;

    Player& GetPlayer(std::size_t index);
    const Player& GetPlayer(std::size_t index) const;
    std::size_t GetPlayerCount() const;

 private:
    void fillCards();
    Card popCard();

 private:
    GameConfig config_;
    GameStatus status_ = GameStatus::ENDED;

    Turn turn_;
    std::vector<Player::Ptr> players_;
    std::set<Card> cards_;
};
}  // namespace Poker

#endif  // POKER_GAME_H
