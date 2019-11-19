// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/Game.h>
#include <Poker/Games/GameEnums.h>

namespace Poker
{
class GameManager final
{
 public:
    static void ProcessGame(Game& game, GameStatus status);
};
}  // namespace Poker
