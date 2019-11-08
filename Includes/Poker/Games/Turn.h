// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_TURN_H
#define POKER_TURN_H

#include <Poker/Games/Player.h>

#include <memory>

namespace Poker
{
class Node
{
 public:
    using Ptr = std::unique_ptr<Node>;

 public:
    Node* next_;
    Player* player_;
};

class Turn
{
 public:
    void GoNext();

	//��Ʈ ��ġ�� ��带 �߰�
    void InsertNode();

	//���� ��ġ�� ��带 ����
    void PopNode();

 private:
    Node* root_;
    Node* now_;

	void GoRoot();
};
}  // namespace Poker

#endif  // !POKER_TURN_H
