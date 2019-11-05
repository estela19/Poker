// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/Player.h>

namespace Poker
{
CardDeck& Player::GetDeck()
{
    return const_cast<CardDeck&>(static_cast<const Player&>(*this).GetDeck());
}

const CardDeck& Player::GetDeck() const
{
    return deck_;
}
}  // namespace Poker
