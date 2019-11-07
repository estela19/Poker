// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_TURN_H
#define POKER_TURN_H

#include <Poker/Games/Player.h>

namespace Poker
{
class Turn
{
 public:
    void GoNext();

	//루트 위치의 노드를 추가
    void InsertNode();

	//다음 위치의 노드를 삭제
    void PopNode();

 private:
    Node::Ptr root_;
    Node::Ptr now_;

	void GoRoot();
};

class Node
{
 public:
    using Ptr = std::unique_ptr<Node>;

 public:
    Node::Ptr next_;
    Player::Ptr player_;
};
}  // namespace Poker

#endif  // !POKER_TURN_H
