// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Cards/card.h>

#include <iostream>

namespace Poker
{
Card::Card(CardShape shape, CardNumber number) : shape_(shape), number_(number)
{
    // Do nothing
}

bool Card::operator>(const Card &c)
{
    if (number_ > c.number_)
        return true;
    else
        return shape_ > c.shape_;
}
}  // namespace Poker
