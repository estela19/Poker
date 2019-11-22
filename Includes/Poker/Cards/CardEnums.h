// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

namespace Poker
{
enum class CardShape
{
    CLOVER,
    HEART,
    DIAMOND,
    SPADE,
    COUNT
};

enum class CardNumber
{
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE,
    COUNT
};

enum class DeckType
{
    INVALID,
    TOP,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    STRAIGHT,
    BACK_STRAIGHT,
    MOUNTAIN,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH,
    BACK_STRAIGHT_FLUSH,
    ROYAL_STRAIGHT_FLUSH,
};
}  // namespace Poker
