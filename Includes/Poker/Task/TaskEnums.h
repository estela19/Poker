#ifndef POKER_TASKENUMS_H
#define POKER_TASKENUMS_H

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
    FOLD
};

enum class CardAction
{
    TAKE,
    OPEN,
    DROP,
    SHUFFLE
};
}  // namespace Poker

#endif  //! _POKER_TASKENUMS_H