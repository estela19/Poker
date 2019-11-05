#ifndef _POKER_BETTINGTASK_H_
#define _POKER_BETTINGTASK_H_

#include <Poker/Task/ITask.h>
#include <Poker/Task/TaskStatus.h>

class BettingTask : public ITask
{
 public:
    TaskStatus Raise(int money);
    TaskStatus Check();
    TaskStatus Call();
    TaskStatus Fold();
};
#endif  // !_POKER_BETTINGTASK_H_
