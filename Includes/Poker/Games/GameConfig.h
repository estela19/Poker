// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_GAME_CONFIG_H
#define POKER_GAME_CONFIG_H

#include <string>
#include <numeric>

namespace Poker
{
struct GameConfig final
{
    int InitCard = 3;
    int MaxCard = 7;
    int RaiseLimit = std::numeric_limits<int>::max();
    int TimeLimit = std::numeric_limits<int>::max();

    std::size_t MaxBetMoney = std::numeric_limits<std::size_t>::max();
    std::size_t MinBetMoney = 0;
    std::size_t InitMoney = 100'000;
};

GameConfig LoadConfig(const std::string& filename);
void SaveConfig(const std::string& filename, const GameConfig& config);
}  // namespace Poker

#endif  // POKER_GAME_CONFIG_H