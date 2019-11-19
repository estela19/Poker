// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Cards/CardDeck.h>

#include <algorithm>

namespace Poker
{
void CardDeck::AddCard(const Card& card)
{
    cards_.emplace_back(card);
}

void CardDeck::RemoveCard(const Card& card)
{
    cards_.erase(std::find(cards_.begin(), cards_.end(), card));
}

void CardDeck::ResetDeck()
{
    cards_.clear();
}

Card& CardDeck::GetCard(std::size_t index)
{
    return const_cast<Card&>(
        static_cast<const CardDeck&>(*this).GetCard(index));
}

const Card& CardDeck::GetCard(std::size_t index) const
{
    return cards_[index];
}

bool CardDeck::Empty() const
{
    return cards_.empty();
}

std::size_t CardDeck::Size() const
{
    return cards_.size();
}

DeckType CardDeck::GetType() const
{
    return DeckType::INVALID;
}
}  // namespace Poker
