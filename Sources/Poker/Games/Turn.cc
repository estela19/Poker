// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/Turn.h>

namespace Poker
{
Turn::~Turn()
{
    while (size_ > 0)
    {
        Pop();
    }
}

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

std::size_t Turn::GetSize() const
{
    return size_;
}

void Turn::Insert(Player::Ptr& player)
{
    Node* tmp = new Node;
    tmp->player_ = player.get();

    if (now_ == nullptr)
    {
        now_ = tmp;
        now_->prev_ = now_;
        now_->next_ = now_;
    }
    else
    {
        tmp->prev_ = now_;
        now_->next_->prev_ = tmp;

        tmp->next_ = now_->next_;
        now_->next_ = tmp;
    }

    ++size_;
}

void Turn::Pop()
{
    Node* node = now_;

    now_ = node->next_;
    now_->prev_ = node->prev_;

    delete node;

    --size_;
}

}  // namespace Poker
