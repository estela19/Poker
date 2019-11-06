// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/GameConfig.h>

#include <fstream>
#include <nlohmann/json.hpp>

namespace Poker
{
GameConfig LoadConfig(const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open config file");
    }

    nlohmann::json j;
    j << file;
    file.close();

    GameConfig config;

    config.InitCard = j["InitCard"];
    config.RaiseLimit = j["RaiseLimit"];
    config.TimeLimit = j["TimeLimit"];

    config.MaxBetMoney = j["MaxBetMoney"].get<std::size_t>();
    config.MinBetMoney = j["MinBetMoney"].get<std::size_t>();
    config.InitMoney = j["InitMoney"].get<std::size_t>();

    return config;
}

void SaveConfig(const std::string& filename, const GameConfig& config)
{
    nlohmann::json j;
    j["InitCard"] = config.InitCard;
    j["RaiseLimit"] = config.RaiseLimit;
    j["TimeLimit"] = config.TimeLimit;

    j["MaxBetMoney"] = config.MaxBetMoney;
    j["MinBetMoney"] = config.MinBetMoney;
    j["InitMoney"] = config.InitMoney;

    std::ofstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open config file");
    }

    file << j;
    file.close();
}
}  // namespace Poker
