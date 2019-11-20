// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Cards/CardDecks.h>

#include <algorithm>
#include <cstring>

namespace Poker
{
DeckType CardDecks::Get(const std::set<Card>& deck)
{
    int shape[4];
    int number[13];
    int shapeCount = 0;
    int numberCount = 0;

    memset(shape, 0, sizeof(shape));
    memset(number, 0, sizeof(number));

    for (const auto& card : deck)
    {
        shape[static_cast<int>(card.Shape())]++;
        number[static_cast<int>(card.Number())]++;
    }

    const int shapeMax = *std::max_element(std::begin(shape), std::end(shape));
    const int numberMax = *std::max_element(std::begin(number), std::end(number));

    for (const auto& i : shape)
    {
        if (i)
            shapeCount++;
    }

    for (const auto& i : number)
    {
        if (i)
            numberCount++;
    }

    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--
    // |  | 2| 3| 4| 5| 6| 7| 8| 9|10| J| Q| K| A|
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--
    // | C|  |  |  |  |  |  |  | 1|  |  | 1|  |  | 2
    // | H| 1|  |  |  |  |  |  |  |  | 1|  |  |  | 2
    // | D| 1|  |  |  |  |  |  |  |  |  |  |  |  | 1
    // | S|  | 1|  |  | 1|  |  |  |  |  |  |  |  | 2 <-- Shape
    // +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--
    // |  | 2| 1|  |  |  |  |  | 1|  | 1| 1|  |  | <-- Number

    if (shapeMax == 5)
    {
        const int flushIdx = std::find(std::begin(shape), std::end(shape), 5) -
                             std::begin(shape);
        int flushNumber[13];
        memset(flushNumber, 0, sizeof(flushNumber));

        for (const auto& card : deck)
        {
            if (static_cast<int>(card.Shape()) == flushIdx)
                flushNumber[static_cast<int>(card.Number())]++;
        }

        if (flushNumber[8] && flushNumber[9] && flushNumber[10] &&
            flushNumber[11] && flushNumber[12])
            return DeckType::ROYAL_STRAIGHT_FLUSH;

        if (flushNumber[0] && flushNumber[1] && flushNumber[2] &&
            flushNumber[3] && flushNumber[12])
            return DeckType::BACK_STRAIGHT_FLUSH;

        for (int i = 0; i < 8; ++i)
        {
            if (flushNumber[i] && flushNumber[i + 1] && flushNumber[i + 2] &&
                flushNumber[i + 3] && flushNumber[i + 4])
                return DeckType::STRAIGHT_FLUSH;
        }

        return DeckType::FLUSH;
    }

    if (numberMax == 4)
        return DeckType::FOUR_OF_A_KIND;

    if (numberMax == 3)
    {
        const std::size_t triIdx =
            std::find(std::begin(number), std::end(number), 3) -
            std::begin(number);
        for (std::size_t i = 0; i < 13; i++)
        {
            if (i != triIdx && number[i] >= 2)
                return DeckType::FULL_HOUSE;
        }
    }

    if (number[8] && number[9] && number[10] && number[11] && number[12])
        return DeckType::MOUNTAIN;

    if (number[0] && number[1] && number[2] && number[3] && number[12])
        return DeckType::BACK_STRAIGHT;

    for (int i = 0; i < 8; ++i)
    {
        if (number[i] && number[i + 1] && number[i + 2] && number[i + 3] &&
            number[i + 4])
            return DeckType::STRAIGHT;
    }

    if (numberMax == 3)
        return DeckType::THREE_OF_A_KIND;

    if (numberMax == 2)
    {
        if (std::count(std::begin(number), std::end(number), 2) > 1)
            return DeckType::TWO_PAIR;

        return DeckType::ONE_PAIR;
    }

    return DeckType::TOP;
}
}  // namespace Poker