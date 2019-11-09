// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/Turn.h>

namespace Poker
{
void Turn::Next()
{
    do
    {
        now_ = now_->next_;
    } while (now_->player_->IsDie());
}

Player* Turn::Current()
{
    return now_->player_;
}

void Turn::Insert()
{
    goRoot();
    Node* tmp = new Node();
    tmp->next_ = now_->next_;
    now_->next_ = tmp;
}

void Turn::Pop()
{
    now_->next_ = now_->next_->next_;
}

void Turn::goRoot()
{
    while (root_ != now_)
    {
        Next();
    }
}

}  // namespace Poker
