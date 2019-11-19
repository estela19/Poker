// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_CARDDECKS_H
#define POKER_CARDDECKS_H

#include <Poker/Cards/CardDeck.h>

#include <unordered_map>

namespace Poker
{
class CardDecks
{
 public:
    DeckType Get(const CardDeck& deck) const;

 private:
    void initRoyalStraightFlush();
    void initBackStraightFlush();
    void initStraightFlush();
    void initFourofaKind();
    void initFullHouse();
    void initFlush();
    void initMountain();
    void initStraight();
    void initThreeofaKind();
    void initTwoPair();
    void initOnePair();
    void initTop();

    std::unordered_map<CardDeck, DeckType> decks_;
};
}  // namespace Poker

#endif  // POKER_CARDDECKS_H