// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef SERVER_GAME_MANAGER_H
#define SERVER_GAME_MANAGER_H

#include <Server/Connection.h>
#include <Poker/Games/Game.h>

#include <deque>
#include <memory>
#include <mutex>

class GameManager final
{
 public:
	//! Delete copy constructor
    GameManager(const GameManager&) = delete;

	//! Delete move constructor
    GameManager(GameManager&&) = delete;

	//! Delete copy assignment operator
	GameManager& operator=(const GameManager&) = delete;
	
	//! Delete move assignment operator
    GameManager& operator=(GameManager&&) = delete;

    void JoinGame(Connection& sess);
    void RemovePlayerFromGame(Poker::Player* player);

    bool HasEmptyGame();

 private:
    std::mutex gameMutex_;
    std::deque<Poker::Game> games_;

 //! Singleton Members
 public:
	static GameManager& Get();

 private:
	//! Default constructor
    GameManager() = default;

	inline static std::unique_ptr<GameManager> instance_;
    inline static std::once_flag onceFlag_;
};

#endif  // SERVER_GAME_MANAGER_H
