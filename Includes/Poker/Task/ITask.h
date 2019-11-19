// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_ITASK_H
#define POKER_ITASK_H

#include <Poker/Players/Player.h>
#include <Poker/Task/TaskEnums.h>

namespace Poker
{
class ITask
{
 public:
    ITask(TaskType type);
    ITask() = default;

    //! Delete copy constructor
    ITask(const ITask&) = delete;

    //! Delete move constructor
    ITask(ITask&&) = delete;

    //! Delete copy assignment operator
    ITask& operator=(const ITask&) = delete;

    //! Delete move assignment operator
    ITask& operator=(ITask&&) = delete;

    void SetPlayer(const Player::Ptr& player);
    const Player& GetPlayer() const;

    TaskStatus Run();

    TaskType GetType() const;

 private:
    virtual TaskStatus Impl(Player& player) = 0;

 private:
    TaskType type_;
    Player* player_ = nullptr;
};
}  // namespace Poker

#endif  // POKER_ITASK_H