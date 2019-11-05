// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H

#include <Poker/Cards/Card.h>

#include <vector>
#include <memory>

namespace Poker
{
class Player final
{
 public:
     using Ptr = std::unique_ptr<Player>;

 public:
    //! Default constructor
    Player() = default;

    //! Delete copy constructor
    Player(const Player&) = delete;

    //! Delete move constructor
    Player(Player&&) = delete;

    //! Delete copy assignment operator
    Player& operator=(const Player&) = delete;

    //! Delete move assignment operator
    Player& operator=(Player&&) = delete;

 private:
    std::vector<Card> cards_;
};
}  // namespace Poker

#endif  // POKER_PLAYER_H
