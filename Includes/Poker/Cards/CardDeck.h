// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_CARD_DECK_H
#define POKER_CARD_DECK_H

#include <Poker/Cards/Card.h>

#include <deque>
#include <functional>

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

    Card& GetCard(std::size_t index);
    const Card& GetCard(std::size_t index) const;

    std::size_t Size() const;
    bool Empty() const;

    DeckType GetType() const;

 private:
    std::deque<Card> cards_;
};
}  // namespace Poker

namespace std
{
template <>
struct hash<Poker::CardDeck>
{
    long long operator()(const Poker::CardDeck& t) const
    {
        long long CardListHash = 0ll;
        std::set<Poker::Card> CardList = t.GetCards();

        for (const auto& card : CardList)
        {
            long long CardTemp = 1ll;
            int NumTemp = 0;

            if (card.Number() != Poker::CardNumber::ACE)
                NumTemp = static_cast<int>(card.Number()) + 1;

            CardTemp << static_cast<int>(card.Shape()) * 13 + NumTemp;

            CardListHash += CardTemp;
        }

        return CardListHash;
    }
};
}  // namespace std

#endif
