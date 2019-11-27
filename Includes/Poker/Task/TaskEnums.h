#ifndef POKER_TASKENUMS_H
#define POKER_TASKENUMS_H

#include <string>

namespace Poker
{
enum class TaskStatus
{
    INVALID,
    STOP,
    COMPLETE,

    NUM_TASKSTATUS
};

enum class TaskType
{
    INVALID,
    BET,
    RAISE,
    CHECK,
    CALL,
    FOLD,
    ALLIN,
    COUNT
};

const std::string TaskTypeStr[] = { "INVALID", "Bet",  "Raise",
                                    "Check",   "Call", "Fold", "AllIn" };

enum class CardAction {
    TAKE,
    OPEN,
    DROP,
    SHUFFLE
};
}  // namespace Poker

#endif  //! _POKER_TASKENUMS_H