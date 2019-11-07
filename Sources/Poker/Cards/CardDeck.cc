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
    cards_.erase(card);
}

const std::set<Card>& CardDeck::GetCards() const
{
    return cards_;
}

bool CardDeck::Empty() const
{
    return cards_.empty();
}
}  // namespace Poker
