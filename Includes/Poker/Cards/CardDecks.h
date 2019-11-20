// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_CARDDECKS_H
#define POKER_CARDDECKS_H

#include <Poker/Cards/CardDeck.h>

#include <set>

namespace Poker
{
class CardDecks
{
 public:
    static DeckType Get(const std::set<Card>& deck);
};
}  // namespace Poker

#endif  // POKER_CARDDECKS_H