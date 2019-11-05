// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_GAME_H
#define POKER_GAME_H

#include <Poker/Games/Player.h>

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

    Player& GetPlayer(std::size_t index);
    const Player& GetPlayer(std::size_t index) const;
    std::size_t GetPlayerCount() const;

 private:
    std::vector<Player::Ptr> players_;
};
}  // namespace Poker

#endif  // POKER_GAME_H
