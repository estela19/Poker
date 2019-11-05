#include "gtest/gtest.h"

#include <Poker/Cards/Card.h>

using namespace Poker;

TEST(CardTests, Compare)
{
    Card c1(CardShape::CLOVER, CardNumber::SEVEN),
        c2(CardShape::HEART, CardNumber::SIX),
        c3(CardShape::CLOVER, CardNumber::SIX);

    EXPECT_TRUE(c1 > c2);
    EXPECT_TRUE(c1 > c3);
    EXPECT_TRUE(c2 > c3);

    Card c4(CardShape::CLOVER, CardNumber::ACE),
        c5(CardShape::HEART, CardNumber::SIX);

    EXPECT_FALSE(c5 > c4);
}