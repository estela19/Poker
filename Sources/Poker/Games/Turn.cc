// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/Turn.h>

namespace Poker
{
void Turn::GoNext()
{
    while (now_->next_->player_->GetisDie() == true)
    {
        now_ = now_->next_;
    }
}

//루트 위치의 노드를 추가
void Turn::InsertNode()
{
    GoRoot();
    Node::Ptr tmp = new Node();
    tmp->next_ = std::move(now_->next_);
    now_->next = std::move(tmp);
}

//다음 노드를 삭제
void Turn::PopNode()
{
    now_->next_ = std::move(now_->next_->next_);
}

void Turn::GoRoot()
{
    while (root_ != now_)
    {
        GoNext();
    }
}

}  // namespace Poker
