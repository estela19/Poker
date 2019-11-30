// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/GameManager.h>
#include <Server/ConnectionPlayer.h>
#include <Server/GameManager.h>

#include <spdlog/spdlog.h>

using namespace std::chrono_literals;

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

    if (game.GetPlayerCount() == 2)
    {
        spdlog::info("[Connection {}] Game started.", conn.ConnectionID());

        std::async(Poker::GameManager::ProcessGame, std::ref(game),
                         Poker::GameStatus::BEGIN_TURN).wait_for(1ms);
    }
}

void GameManager::RemovePlayerFromGame(Poker::Player* player)
{
    auto& refPlayer = static_cast<ConnectionPlayer&>(*player);

    std::size_t playerIdx = (refPlayer.ID == 0) ? 1 : 0;
    auto& p =
        static_cast<ConnectionPlayer&>(player->GetGame().GetPlayer(playerIdx));

    p.conn.Write(R"({
		"Type": 7
		})");

    p.conn.Stop();
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
