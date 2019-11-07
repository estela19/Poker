// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H

#include <Poker/Cards/CardDeck.h>

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

    void SetMoney(std::size_t money);
    std::size_t GetMoney() const;

    CardDeck& GetDeck();
    const CardDeck& GetDeck() const;

	bool GetisDie() const;

 private:
    std::size_t money_;

    CardDeck deck_;

	bool isDie_;
};
}  // namespace Poker

#endif  // POKER_PLAYER_H
