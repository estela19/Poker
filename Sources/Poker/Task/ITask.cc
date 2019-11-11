// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Task/ITask.h>

#include <iostream>

namespace Poker
{
TaskStatus ITask::Run()
{
    return Impl();
}
}  // namespace Poker
