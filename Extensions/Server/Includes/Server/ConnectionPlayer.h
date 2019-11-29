// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef SERVER_SESSION_PLAYER_H
#define SERVER_SESSION_PLAYER_H

#include <Poker/Players/Player.h>
#include <Server/Connection.h>

class ConnectionPlayer final : public Poker::Player
{
 public:
    ConnectionPlayer(Connection& conn);

    std::size_t RequireOpenCard() const override;
    Poker::ITask::Ptr RequireBetting() const override;

    Connection& conn;
};

#endif  // SERVER_SESSION_PLAYER_H
