#ifndef POKER_TASKENUMS_H
#define POKER_TASKENUMS_H

enum class TaskStatus
{
    INVALID,
    STOP,
    COMPLETE,

    NUM_TASKSTATUS
};

enum class Betting
{
    RAISE,
    CHECK,
	OK,
    FOLD
};

enum class CardAction
{
	TAKE,
	OPEN,
	DROP,
	SHUFFLE
};

#endif  //! _POKER_TASKENUMS_H