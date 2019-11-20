// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_CARDDECKS_H
#define POKER_CARDDECKS_H

#include <Poker/Cards/CardDeck.h>

#include <set>
#include <array>

namespace Poker
{
class CardDecks
{
 public:
    static DeckType Get(const std::set<Card>& deck);

 private:
    static DeckType GetFlush(const std::set<Card>& deck,
                             const std::array<int, 4>& shape);
    static DeckType GetNonFlush(const std::array<int, 13>& number);
};
}  // namespace Poker

#endif  // POKER_CARDDECKS_H