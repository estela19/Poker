// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Players/Player.h>
#include <Poker/Task/Betting/FoldTask.h>

namespace Poker
{
TaskStatus FoldTask::Impl(Player& player)
{
    // player die
    player.SetDie(true);

    // card deck reset
    player.GetDeck().Clear();

    // prebet reset
    player.SetPreBet(0);

    return TaskStatus::COMPLETE;
}

FoldTask::FoldTask()
{
    // Do nothing
}
}  // namespace Poker
