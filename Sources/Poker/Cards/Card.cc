// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Cards/Card.h>

#include <iostream>

namespace Poker
{
Card::Card(CardShape shape, CardNumber number) : shape_(shape), number_(number)
{
    // Do nothing
}

bool Card::operator>(const Card& c) const
{
    if (number_ == c.number_)
        return shape_ > c.shape_;

    return number_ > c.number_;
}

bool Card::operator<(const Card& c) const
{
    if (number_ == c.number_)
        return shape_ < c.shape_;

    return number_ < c.number_;
}

bool Card::operator>=(const Card& c) const
{
    if (number_ == c.number_)
        return shape_ >= c.shape_;

    return number_ > c.number_;
}

bool Card::operator<=(const Card& c) const
{
    if (number_ == c.number_)
        return shape_ <= c.shape_;

    return number_ < c.number_;
}

bool Card::operator==(const Card& c) const
{
    if (number_ == c.number_ && shape_ == c.shape_)
        return true;
    return false;
}

bool Card::operator!=(const Card& c) const
{
    if (number_ == c.number_ && shape_ == c.shape_)
        return false;
    return true;
}

CardShape Card::Shape() const
{
    return shape_;
}

CardNumber Card::Number() const
{
    return number_;
}
}  // namespace Poker
