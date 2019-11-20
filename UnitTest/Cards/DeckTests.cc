#include "gtest/gtest.h"

#include <Poker/Cards/CardDecks.h>

using namespace Poker;

TEST(DeckTests, Deck)
{
    CardDeck cd;
    const Card c1(CardShape::CLOVER, CardNumber::SEVEN),
        c2(CardShape::HEART, CardNumber::SIX);

    EXPECT_TRUE(cd.Empty());

    cd.AddCard(c1);
    cd.AddCard(c2);

    EXPECT_EQ(cd.Size(), 2);

    const Card c3 = cd.GetCard(0);
    Card c4 = cd.GetCard(1);

    EXPECT_EQ(c3.Shape(), CardShape::CLOVER);
    EXPECT_EQ(c3.Number(), CardNumber::SEVEN);
    EXPECT_EQ(c4.Shape(), CardShape::HEART);
    EXPECT_EQ(c4.Number(), CardNumber::SIX);

    cd.RemoveCard(c2);
    EXPECT_EQ(cd.Size(), 1);

    cd.RemoveCard(c1);
    EXPECT_TRUE(cd.Empty());
}

TEST(DeckTests, GetRoyalStraightFlush)
{
    CardDeck cd;
    const Card c1(CardShape::CLOVER, CardNumber::ACE),
        c2(CardShape::CLOVER, CardNumber::TEN),
        c3(CardShape::CLOVER, CardNumber::JACK),
        c4(CardShape::CLOVER, CardNumber::QUEEN),
        c5(CardShape::CLOVER, CardNumber::KING);

    cd.AddCard(c1);
    cd.AddCard(c2);
    cd.AddCard(c3);
    cd.AddCard(c4);
    cd.AddCard(c5);

    EXPECT_EQ(cd.GetType(), DeckType::ROYAL_STRAIGHT_FLUSH);
}

TEST(DeckTests, GetBackStraightFlush)
{
    CardDeck cd;
    const Card c1(CardShape::CLOVER, CardNumber::ACE),
        c2(CardShape::CLOVER, CardNumber::TWO),
        c3(CardShape::CLOVER, CardNumber::THREE),
        c4(CardShape::CLOVER, CardNumber::FOUR),
        c5(CardShape::CLOVER, CardNumber::FIVE);

    cd.AddCard(c1);
    cd.AddCard(c2);
    cd.AddCard(c3);
    cd.AddCard(c4);
    cd.AddCard(c5);

    EXPECT_EQ(cd.GetType(), DeckType::BACK_STRAIGHT_FLUSH);
}

TEST(DeckTests, GetStraightFlush)
{
    CardDeck cd;
    const Card c1(CardShape::CLOVER, CardNumber::SEVEN),
        c2(CardShape::CLOVER, CardNumber::EIGHT),
        c3(CardShape::CLOVER, CardNumber::NINE),
        c4(CardShape::CLOVER, CardNumber::TEN),
        c5(CardShape::CLOVER, CardNumber::JACK);

    cd.AddCard(c1);
    cd.AddCard(c2);
    cd.AddCard(c3);
    cd.AddCard(c4);
    cd.AddCard(c5);

    EXPECT_EQ(cd.GetType(), DeckType::STRAIGHT_FLUSH);
}

TEST(DeckTests, GetFourofaKind)
{
    CardDeck cd;
    const Card c1(CardShape::CLOVER, CardNumber::ACE),
        c2(CardShape::HEART, CardNumber::ACE),
        c3(CardShape::DIAMOND, CardNumber::ACE),
        c4(CardShape::SPADE, CardNumber::ACE),
        c5(CardShape::CLOVER, CardNumber::TWO);

    cd.AddCard(c1);
    cd.AddCard(c2);
    cd.AddCard(c3);
    cd.AddCard(c4);
    cd.AddCard(c5);

    EXPECT_EQ(cd.GetType(), DeckType::FOUR_OF_A_KIND);
}

TEST(DeckTests, GetFullHouse)
{
    CardDeck cd;
    const Card c1(CardShape::CLOVER, CardNumber::ACE),
        c2(CardShape::DIAMOND, CardNumber::ACE),
        c3(CardShape::SPADE, CardNumber::ACE),
        c4(CardShape::CLOVER, CardNumber::TWO),
        c5(CardShape::DIAMOND, CardNumber::TWO);

    cd.AddCard(c1);
    cd.AddCard(c2);
    cd.AddCard(c3);
    cd.AddCard(c4);
    cd.AddCard(c5);

    EXPECT_EQ(cd.GetType(), DeckType::FULL_HOUSE);
}

TEST(DeckTests, GetFlush)
{
    CardDeck cd;
    const Card c1(CardShape::CLOVER, CardNumber::ACE),
        c2(CardShape::CLOVER, CardNumber::THREE),
        c3(CardShape::CLOVER, CardNumber::FIVE),
        c4(CardShape::CLOVER, CardNumber::SEVEN),
        c5(CardShape::CLOVER, CardNumber::NINE);

    cd.AddCard(c1);
    cd.AddCard(c2);
    cd.AddCard(c3);
    cd.AddCard(c4);
    cd.AddCard(c5);

    EXPECT_EQ(cd.GetType(), DeckType::FLUSH);
}

TEST(DeckTests, GetMountain)
{
    CardDeck cd;
    const Card c1(CardShape::CLOVER, CardNumber::ACE),
        c2(CardShape::HEART, CardNumber::KING),
        c3(CardShape::SPADE, CardNumber::QUEEN),
        c4(CardShape::DIAMOND, CardNumber::JACK),
        c5(CardShape::CLOVER, CardNumber::TEN);

    cd.AddCard(c1);
    cd.AddCard(c2);
    cd.AddCard(c3);
    cd.AddCard(c4);
    cd.AddCard(c5);

    EXPECT_EQ(cd.GetType(), DeckType::MOUNTAIN);
}

TEST(DeckTests, GetBackStraight)
{
    CardDeck cd;
    const Card c1(CardShape::CLOVER, CardNumber::ACE),
        c2(CardShape::HEART, CardNumber::TWO),
        c3(CardShape::DIAMOND, CardNumber::THREE),
        c4(CardShape::SPADE, CardNumber::FOUR),
        c5(CardShape::CLOVER, CardNumber::FIVE);

    cd.AddCard(c1);
    cd.AddCard(c2);
    cd.AddCard(c3);
    cd.AddCard(c4);
    cd.AddCard(c5);

    EXPECT_EQ(cd.GetType(), DeckType::BACK_STRAIGHT);
}

TEST(DeckTests, GetStraight)
{
    CardDeck cd;
    const Card c1(CardShape::CLOVER, CardNumber::SIX),
        c2(CardShape::HEART, CardNumber::TWO),
        c3(CardShape::DIAMOND, CardNumber::THREE),
        c4(CardShape::SPADE, CardNumber::FOUR),
        c5(CardShape::CLOVER, CardNumber::FIVE);

    cd.AddCard(c1);
    cd.AddCard(c2);
    cd.AddCard(c3);
    cd.AddCard(c4);
    cd.AddCard(c5);

    EXPECT_EQ(cd.GetType(), DeckType::STRAIGHT);
}

TEST(DeckTests, GetThreeofaKind)
{
    CardDeck cd;
    const Card c1(CardShape::CLOVER, CardNumber::TWO),
        c2(CardShape::HEART, CardNumber::TWO),
        c3(CardShape::DIAMOND, CardNumber::TWO),
        c4(CardShape::SPADE, CardNumber::FOUR),
        c5(CardShape::CLOVER, CardNumber::FIVE);

    cd.AddCard(c1);
    cd.AddCard(c2);
    cd.AddCard(c3);
    cd.AddCard(c4);
    cd.AddCard(c5);

    EXPECT_EQ(cd.GetType(), DeckType::THREE_OF_A_KIND);
}

TEST(DeckTests, GetTwoPair)
{
    CardDeck cd;
    const Card c1(CardShape::CLOVER, CardNumber::TWO),
        c2(CardShape::HEART, CardNumber::TWO),
        c3(CardShape::DIAMOND, CardNumber::THREE),
        c4(CardShape::SPADE, CardNumber::THREE),
        c5(CardShape::CLOVER, CardNumber::FIVE);

    cd.AddCard(c1);
    cd.AddCard(c2);
    cd.AddCard(c3);
    cd.AddCard(c4);
    cd.AddCard(c5);

    EXPECT_EQ(cd.GetType(), DeckType::TWO_PAIR);
}

TEST(DeckTests, GetOnePair)
{
    CardDeck cd;
    const Card c1(CardShape::CLOVER, CardNumber::TWO),
        c2(CardShape::HEART, CardNumber::TWO),
        c3(CardShape::DIAMOND, CardNumber::THREE),
        c4(CardShape::SPADE, CardNumber::FOUR),
        c5(CardShape::CLOVER, CardNumber::FIVE);

    cd.AddCard(c1);
    cd.AddCard(c2);
    cd.AddCard(c3);
    cd.AddCard(c4);
    cd.AddCard(c5);

    EXPECT_EQ(cd.GetType(), DeckType::ONE_PAIR);
}

TEST(DeckTests, GetTop)
{
    CardDeck cd;
    const Card c1(CardShape::CLOVER, CardNumber::TWO),
        c2(CardShape::HEART, CardNumber::FOUR),
        c3(CardShape::DIAMOND, CardNumber::SIX),
        c4(CardShape::SPADE, CardNumber::EIGHT),
        c5(CardShape::CLOVER, CardNumber::TEN);

    cd.AddCard(c1);
    cd.AddCard(c2);
    cd.AddCard(c3);
    cd.AddCard(c4);
    cd.AddCard(c5);

    EXPECT_EQ(cd.GetType(), DeckType::TOP);
}