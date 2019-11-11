// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/Player.h>

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
}  // namespace Poker
