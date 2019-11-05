// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_CARD_H
#define POKER_CARD_H

#include <Poker/Cards/CardEnums.h>

namespace Poker
{
class Card
{
 public:
    Card(CardShape shape, CardNumber number);

    bool operator>(const Card &c);
    bool operator<(const Card &c);
    bool operator>=(const Card &c);
    bool operator<=(const Card &c);
    bool operator==(const Card &c);
    bool operator!=(const Card &c);

    CardShape Shape() const;
    CardNumber Number() const;

 private:
    const CardShape shape_;
    const CardNumber number_;
};
}  // namespace Poker

#endif  // POKER_CARD_H
