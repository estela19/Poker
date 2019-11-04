#include "gtest/gtest.h"

#include <Poker/Cards/card.h>

TEST(CardTests, TEST01) {
    Card c1(clover, seven), c2(heart, six), c3(clover, six);
    
    EXPECT_EQ(c1 > c2, 1);
    EXPECT_EQ(c1 > c3, 1);
    EXPECT_EQ(c2 > c3, 1);
}