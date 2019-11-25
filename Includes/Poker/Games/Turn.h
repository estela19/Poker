// Copyright(C) 2019 Sooyeon Kim, Gyeonguk Chae, Junyeong Park

#ifndef POKER_TURN_H
#define POKER_TURN_H

#include <Poker/Players/Player.h>

#include <memory>

namespace Poker
{
class Turn
{
 private:
    struct Node
    {
        Node* next = nullptr;
        Player* player = nullptr;
    };

 public:
    ~Turn();

    void Next();
    Player* Current();
    std::size_t GetSize() const;

    void Insert(Player::Ptr& player);
    void Pop();

    template <typename FuncT>
    void ForEach(FuncT&& func)
    {
        if (now_->player->IsDie())
        {
            throw std::logic_error("Cannot start foreach with folded player");
        }

        Node* const first = now_;

        do
        {
            func(now_->player);
            Next();
        } while (first != now_);
    }

    template <typename FuncT>
    void ForEachAll(FuncT&& func)
    {
        Node* const first = now_;
        Node* now = now_;

        do
        {
            func(now->player);
            now = now->next;
        } while (first != now);
    }

 private:
    Node* now_ = nullptr;
    std::size_t size_ = 0;
};
}  // namespace Poker

#endif  // !POKER_TURN_H
