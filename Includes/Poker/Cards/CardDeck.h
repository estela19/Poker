// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_CARD_DECK_H
#define POKER_CARD_DECK_H

#include <Poker/Cards/Card.h>

#include <deque>
#include <set>

namespace Poker
{
enum class DeckType
{
    INVALID,
    ROYAL_STRAIGHT_FLUSH,
    BACK_STRAIGHT_FLUSH,
    STRAIGHT_FLUSH,
    FOUR_OF_A_KIND,
    FULL_HOUSE,
    FLUSH,
    MOUNTAIN,
    BACK_STRAIGHT,
    STRAIGHT,
    THREE_OF_A_KIND,
    TWO_PAIR,
    ONE_PAIR,
    TOP
};

class CardDeck final
{
 public:
    void AddCard(const Card& card);
    void RemoveCard(const Card& card);

    std::set<Card> GetCardSet() const;
    Card& GetCard(std::size_t index);
    const Card& GetCard(std::size_t index) const;

    std::size_t Size() const;
    bool Empty() const;

    DeckType GetType() const;

 private:
    std::deque<Card> cards_;
};
}  // namespace Poker

#endif
