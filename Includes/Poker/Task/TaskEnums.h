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

enum class BettingStatus
{
    INVALID,
	BET,	//money
    RAISE,	//money
    CHECK,	//
    CALL,	//
    FOLD	//
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