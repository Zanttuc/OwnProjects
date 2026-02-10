#pragma once
#include "deck.h"

class Player {
public:
    static const int BUST = 22;

    Player(const std::string& name)
        : hand(), status(DEFAULT), handValue(0), name(name)
    {}

    std::vector<Card> hand;
    Status status;
    int handValue;
    std::string name;
};

class Dealer : public Player
{
public:
    static const int MAX_DRAW = 17;
    Dealer() : Player("Dealer")
    {}
};
