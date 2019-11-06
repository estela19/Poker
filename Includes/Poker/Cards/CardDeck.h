// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_CARD_DECK_H
#define POKER_CARD_DECK_H

#include <Poker/Cards/Card.h>

#include <set>

namespace Poker
{
class CardDeck final
{
 public:
    void AddCard(const Card& card);
    void RemoveCard(const Card& card);
    const std::set<Card>& GetCards() const;

 private:
    std::set<Card> cards_;
};
}  // namespace Poker

#endif
