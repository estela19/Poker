#ifndef _POKER_CARDTASK_H_
#endif _POKER_CARDTASK_H_

#include <Poker/Task/ITask.h>
#include <Poker/Task/TaskStatus.h>

class CardTask : public ITask
{
 public:
    TaskStatus OpenCard();
};

#endif  // !_POKER_CARDTASK_H_
