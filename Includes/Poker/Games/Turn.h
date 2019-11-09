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
    class Node
    {
     public:
        Node* next_;
        Player* player_;
    };

 public:
    void Next();
    Player* Current();

    void Insert();
    void Pop();

 private:
    Node* root_;
    Node* now_;

    void goRoot();
};
}  // namespace Poker

#endif  // !POKER_TURN_H
