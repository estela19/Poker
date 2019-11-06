// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_GAME_CONFIG_H
#define POKER_GAME_CONFIG_H

#include <string>

namespace Poker
{
struct GameConfig final
{
    int InitCard;
    int RaiseLimit;
    int TimeLimit;

    std::size_t MaxBetMoney;
    std::size_t MinBetMoney;
    std::size_t InitMoney;
};

GameConfig LoadConfig(const std::string& filename);
void SaveConfig(const std::string& filename, const GameConfig& config);
}  // namespace Poker

#endif  // POKER_GAME_CONFIG_H