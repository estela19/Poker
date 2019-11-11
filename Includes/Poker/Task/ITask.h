// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_ITASK_H
#define POKER_ITASK_H

#include <Poker/Task/TaskEnums.h>

namespace Poker
{
class ITask
{
 public:
    ITask() = default;

    //! Delete copy constructor
    ITask(const ITask&) = delete;

    //! Delete move constructor
    ITask(ITask&&) = delete;

    //! Delete copy assignment operator
    ITask& operator=(const ITask&) = delete;

    //! Delete move assignment operator
    ITask& operator=(ITask&&) = delete;

    TaskStatus Run();

 private:
    virtual TaskStatus Impl() = 0;
};
}  // namespace Poker

#endif  // POKER_ITASK_H