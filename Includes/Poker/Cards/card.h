#pragma once

enum CardShape {
    clover = 0,
    heart,
    diamond,
    spade
};

enum CardNumber {
    two = 2,
    three,
    four,
    five,
    six,
    seven,
    eight,
    nine,
    ten,
    jack,
    queen,
    king,
    ace
};

class Card {
    private:
    const CardShape shape_;
    const CardNumber number_;

    public:
    Card(CardShape shape, CardNumber number);
    void PrintCard();
    bool operator > (Card &c);
};

Card::Card(CardShape shape, CardNumber number) : shape_(shape), number_(number) {
    // do nothing
}

void Card::PrintCard() {
    std::cout << shape_ << ' ' << number_ << '\n';
}

bool Card::operator > (Card &c) {
    if(number_ > c.number_) return true;
    else return shape_ > c.shape_;
}