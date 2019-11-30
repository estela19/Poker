// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef SERVER_SESSION_PLAYER_H
#define SERVER_SESSION_PLAYER_H

#include <Poker/Players/Player.h>
#include <Server/Connection.h>

#include <nlohmann/json.hpp>

class ConnectionPlayer final : public Poker::Player
{
 public:
    ConnectionPlayer(Connection& conn);

	void OnGameStarted() override;
    std::size_t RequireOpenCard() override;
    Poker::ITask::Ptr RequireBetting() override;

    Connection& conn;
    std::string name;
    std::size_t ID;

 private:
    void addType(nlohmann::json& j, int type) const;
    void addMyName(nlohmann::json& j) const;
    void addOpName(nlohmann::json& j) const;
    void addMyCardList(nlohmann::json& j) const;
    void addOpCardList(nlohmann::json& j) const;
    void addMyMoney(nlohmann::json& j) const;
    void addOpMoney(nlohmann::json& j) const;
    void addTotalMoney(nlohmann::json& j) const;
    void addValidBetMoney(nlohmann::json& j) const;
    void addValid(nlohmann::json& j) const;
    void addWinner(nlohmann::json& j) const;
};

#endif  // SERVER_SESSION_PLAYER_H
