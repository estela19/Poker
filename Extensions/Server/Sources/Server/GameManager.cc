// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Server/GameManager.h>
#include <Server/ConnectionPlayer.h>

#include <spdlog/spdlog.h>

void GameManager::JoinGame(Connection& conn)
{
    if (!HasEmptyGame())
    {
        std::lock_guard<std::mutex> lock(gameMutex_);

        Poker::GameConfig config;
        games_.emplace_back(config);

		spdlog::info("[Connection {}] Create new game", conn.ConnectionID());
	}

	auto& game = games_.back();
	game.AddPlayer<ConnectionPlayer>(conn);
    spdlog::info("[Connection {}] New player added.", conn.ConnectionID());
}

bool GameManager::HasEmptyGame()
{
    std::lock_guard<std::mutex> lock(gameMutex_);

    if (games_.empty())
        return false;

    return games_.back().GetPlayerCount() < 2;
}

GameManager& GameManager::Get()
{
    std::call_once(onceFlag_, []() { instance_.reset(new GameManager); });

    return *(instance_.get());
}
