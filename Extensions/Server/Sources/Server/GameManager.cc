// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/GameManager.h>
#include <Server/ConnectionPlayer.h>
#include <Server/GameManager.h>

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

    if (game.GetPlayerCount() == 2)
    {
        spdlog::info("[Connection {}] Game started.", conn.ConnectionID());

        (void)std::async(Poker::GameManager::ProcessGame, std::ref(game),
                         Poker::GameStatus::BEGIN_TURN);
    }
}

void GameManager::RemovePlayerFromGame(Poker::Player* player)
{
    auto& refPlayer = static_cast<ConnectionPlayer&>(*player);

    std::size_t playerIdx = 0;
    for (std::size_t i = 0; i < player->GetGame().GetPlayerCount(); ++i)
    {
        auto& p =
            static_cast<ConnectionPlayer&>(player->GetGame().GetPlayer(i));

        if (p.conn.ConnectionID() != refPlayer.conn.ConnectionID())
        {
            p.conn.Write(R"({
				"Type": 7
				})");

			p.conn.Stop();
        }
        else
        {
            playerIdx = i;
        }
    }

    games_.erase(std::find_if(
        begin(games_), end(games_),
        [&refPlayer, &playerIdx](const Poker::Game& game) {
            return (
                static_cast<const ConnectionPlayer&>(game.GetPlayer(playerIdx))
                    .conn.ConnectionID() == refPlayer.conn.ConnectionID());
        }));
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
