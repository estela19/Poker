#include "gtest/gtest.h"

#include <Poker/Cards/Card.h>

using namespace Poker;

TEST(CardTests, TEST01)
{
    Card c1(CardShape::CLOVER, CardNumber::SEVEN),
        c2(CardShape::HEART, CardNumber::SIX),
        c3(CardShape::CLOVER, CardNumber::SIX);

    EXPECT_EQ(c1 > c2, 1);
    EXPECT_EQ(c1 > c3, 1);
    EXPECT_EQ(c2 > c3, 1);
}