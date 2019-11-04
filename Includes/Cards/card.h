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
    CardShape shape;
    CardNumber number;

    public:
    void PrintCard();
    bool operator > (Card &c);
};

bool Card::operator > (Card &c) {
    if(shape > c.shape) return true;
    else return number > c.number;
}

void Card::PrintCard() {
    std::cout << shape << ' ' << number << '\n';
}