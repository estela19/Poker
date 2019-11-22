// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_CARD_DECK_H
#define POKER_CARD_DECK_H

#include <Poker/Cards/Card.h>

#include <deque>
#include <set>

namespace Poker
{
class CardDeck final
{
 public:
    void AddCard(const Card& card);
    void RemoveCard(const Card& card);
    void Clear();

    std::set<Card> GetCardSet() const;
    Card& GetCard(std::size_t index);
    const Card& GetCard(std::size_t index) const;

    std::size_t Size() const;
    bool Empty() const;

    DeckType GetType() const;
    DeckType GetOpenType() const;

 private:
    std::deque<Card> cards_;
};
}  // namespace Poker

#endif
