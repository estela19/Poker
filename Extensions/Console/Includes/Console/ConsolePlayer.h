// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_CONSOLE_CONSOLE_PLAYER_H
#define POKER_CONSOLE_CONSOLE_PLAYER_H

#include <Poker/Players/Player.h>

class ConsolePlayer : public Poker::Player
{
 public:
    ConsolePlayer(std::size_t playerId);

    std::size_t RequireOpenCard() const override;
    Poker::ITask::Ptr RequireBetting() const override;
    void OnBettingDone() const override;
    void SuccessFlag() const override;

	std::string ToString() const override;

	std::string PlayerCardListToString() const;
    void PrintCardList() const;

 private:
    std::size_t playerId_;
};

#endif  // POKER_CONSOLE_CONSOLE_PLAYER_H
