// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Cards/CardDeck.h>

namespace Poker
{
void CardDeck::AddCard(const Card& card)
{
    cards_.emplace(card);
}

void CardDeck::RemoveCard(const Card& card)
{
    cards_.emplace(card);
}

const std::set<Card>& CardDeck::GetCards() const
{
    return cards_;
}
}  // namespace Poker