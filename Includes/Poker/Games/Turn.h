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

	//��Ʈ ��ġ�� ��带 �߰�
    void InsertNode();

	//���� ��ġ�� ��带 ����
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
