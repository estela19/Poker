// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#include <Poker/Games/Turn.h>

#include <stdexcept>

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
        now_ = now_->next;
    } while (now_->player->IsDie());
}

Player* Turn::Current()
{
    if (now_ == nullptr)
    {
        throw std::logic_error("No player inserted");
    }

    return now_->player;
}

std::size_t Turn::GetSize() const
{
    return size_;
}

void Turn::Insert(Player::Ptr& player)
{
    Node* node = new Node;
    node->player = player.get();

    if (now_ == nullptr)
    {
        now_ = node;
        node->next = node;
    }
    else
    {
        Node* last = now_;
        while (last->next != now_)
            last = last->next;

        node->next = now_;
        now_ = node;
        last->next = now_;
    }

    ++size_;
}

void Turn::Pop()
{
    if (now_ == nullptr)
    {
        return;
    }

    Node* last = now_;
    while (last->next != now_)
        last = last->next;

    Node* tmp = now_;

    if (last == now_)
    {
        now_ = nullptr;
    }
    else
    {
        now_ = now_->next;
        last->next = now_;
    }

    delete tmp;

    --size_;
}
}  // namespace Poker
