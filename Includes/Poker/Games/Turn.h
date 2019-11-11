// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_TURN_H
#define POKER_TURN_H

#include <Poker/Games/Player.h>

#include <memory>

namespace Poker
{
class Turn
{
 private:
    struct Node
    {
        Node* next = nullptr;
        Player* player;
    };

 public:
    ~Turn();

    void Next();
    Player* Current();
    std::size_t GetSize() const;

    void Insert(Player::Ptr& player);
    void Pop();

 private:
    Node* now_ = nullptr;
    std::size_t size_ = 0;
};
}  // namespace Poker

#endif  // !POKER_TURN_H
