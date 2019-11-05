#include "gtest/gtest.h"

#include <Poker/Cards/Card.h>

using namespace Poker;

TEST(CardTests, Operator)
{
    Card c1(CardShape::CLOVER, CardNumber::SEVEN),
        c2(CardShape::HEART, CardNumber::SIX),
        c3(CardShape::CLOVER, CardNumber::SIX),
        c4(CardShape::CLOVER, CardNumber::ACE),
        c5(CardShape::HEART, CardNumber::SIX),
        c6(CardShape::HEART, CardNumber::SIX);

    EXPECT_TRUE(c1 > c2);
    EXPECT_TRUE(c1 > c3);
    EXPECT_TRUE(c2 > c3);
    EXPECT_FALSE(c5 > c4);
    EXPECT_FALSE(c5 > c6);

    EXPECT_TRUE(c1 >= c2);
    EXPECT_TRUE(c1 >= c3);
    EXPECT_TRUE(c2 >= c3);
    EXPECT_FALSE(c5 >= c4);
    EXPECT_TRUE(c5 >= c6);

    EXPECT_FALSE(c1 < c2);
    EXPECT_FALSE(c1 < c3);
    EXPECT_FALSE(c2 < c3);
    EXPECT_TRUE(c5 < c4);
    EXPECT_FALSE(c5 < c6);

    EXPECT_FALSE(c1 <= c2);
    EXPECT_FALSE(c1 <= c3);
    EXPECT_FALSE(c2 <= c3);
    EXPECT_TRUE(c5 <= c4);
    EXPECT_TRUE(c5 <= c6);

    EXPECT_FALSE(c1 == c2);
    EXPECT_FALSE(c1 == c3);
    EXPECT_FALSE(c2 == c3);
    EXPECT_FALSE(c5 == c4);
    EXPECT_TRUE(c5 == c6);

    EXPECT_TRUE(c1 != c2);
    EXPECT_TRUE(c1 != c3);
    EXPECT_TRUE(c2 != c3);
    EXPECT_TRUE(c5 != c4);
    EXPECT_FALSE(c5 != c6);
}

TEST(CardTests, Constructor) {
    Card c1(CardShape::CLOVER, CardNumber::SEVEN),
        c2(CardShape::HEART, CardNumber::SIX);

    EXPECT_EQ(c1.Shape(), CardShape::CLOVER);
    EXPECT_EQ(c2.Shape(), CardShape::HEART);
    EXPECT_EQ(c1.Number(), CardNumber::SEVEN);
    EXPECT_EQ(c2.Number(), CardNumber::SIX);
}