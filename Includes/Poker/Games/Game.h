// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_GAME_H
#define POKER_GAME_H

#include <Poker/Games/GameEnums.h>
#include <Poker/Games/Player.h>
#include <Poker/Task/ITask.h>

#include <vector>

namespace Poker
{
class Game final
{
 public:
    template <typename PlayerT, typename... Args>
    void AddPlayer(Args&&... args)
    {
        players_.emplace_back(std::make_unique<PlayerT>(std::move(args)...));
    }

    void BeginTurn();
    void EndTurn();
    void Process(std::size_t id, ITask&& task);

    Player& GetPlayer(std::size_t index);
    const Player& GetPlayer(std::size_t index) const;
    std::size_t GetPlayerCount() const;

 private:
    GameStatus status_ = GameStatus::ENDED;

    std::vector<Player::Ptr> players_;
};
}  // namespace Poker

#endif  // POKER_GAME_H
