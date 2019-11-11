// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_CARD_DECK_H
#define POKER_CARD_DECK_H

#include <Poker/Cards/Card.h>

#include <set>

namespace Poker
{
enum class DeckType
{
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

    const std::set<Card>& GetCards() const;
    bool Empty() const;

 private:
    std::set<Card> cards_;
};
}  // namespace Poker

namespace std
{
template <>
struct hash<Poker::CardDeck>
{
    long long operator()(const Poker::CardDeck& t) const
    {
        [[maybe_unused]] long long cardList = (1ll << 52) - 1;

        return 0;
    }
};
}  // namespace std

#endif
