// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_PLAYER_H
#define POKER_PLAYER_H

#include <Poker/Cards/CardDeck.h>

#include <memory>
#include <string>

namespace Poker
{
class Game;

class Player
{
 public:
    using Ptr = std::unique_ptr<Player>;

 public:
    //! Default constructor
    Player() = default;

    //! Default destructor
    virtual ~Player() = default;

    //! Delete copy constructor
    Player(const Player&) = delete;

    //! Delete move constructor
    Player(Player&&) = delete;

    //! Delete copy assignment operator
    Player& operator=(const Player&) = delete;

    //! Delete move assignment operator
    Player& operator=(Player&&) = delete;

    void SetGame(Game* game);
    Game& GetGame();
    const Game& GetGame() const;

    void SetMoney(std::size_t money);
    std::size_t GetMoney() const;

	void SetPreBet(std::size_t money);
    std::size_t GetPreBet() const;

    CardDeck& GetDeck();
    const CardDeck& GetDeck() const;

    void SetDie(bool die);
	bool IsDie() const;

    virtual std::size_t RequireOpenCard() const = 0;

    virtual std::string ToString() const;

 private:
    std::size_t money_;
    std::size_t preBet_;

    CardDeck deck_;
    Game* game_;

	bool isDie_ = false;
};
}  // namespace Poker

#endif  // POKER_PLAYER_H
