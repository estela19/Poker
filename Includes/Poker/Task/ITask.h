#ifndef _POKER_ITASK_H
#define _POKER_ITASK_H

#include <Poker/Task/TaskStatus.h>

namespace Poker
{
class ITask
{
 public:
    ITask() = default;

 private:
    virtual TaskStatus Impl() = 0;
};
}  // namespace Poker

#endif  // POKER_ITASK_H