// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Players/Player.h>

#include <sstream>

namespace Poker
{
void Player::SetMoney(std::size_t money)
{
    money_ = money;
}

std::size_t Player::GetMoney() const
{
    return money_;
}

CardDeck& Player::GetDeck()
{
    return const_cast<CardDeck&>(static_cast<const Player&>(*this).GetDeck());
}

void Player::SetGame(Game* game)
{
    game_ = game;
}

Game& Player::GetGame()
{
    return const_cast<Game&>(static_cast<const Player&>(*this).GetGame());
}

const Game& Player::GetGame() const
{
    return *game_;
}

const CardDeck& Player::GetDeck() const
{
    return deck_;
}

void Player::SetDie(bool die)
{
    isDie_ = die;
}

bool Player::IsDie() const
{
    return isDie_;
}

std::string Player::ToString() const
{
    std::stringstream ss;

    ss << "[Player] Money(" << money_ << ") Dead?(" << std::boolalpha << isDie_
       << ")";

    return ss.str();
}
}  // namespace Poker
