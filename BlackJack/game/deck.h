#pragma once
#include "structs.h"

class Deck {
public:
    static const int MAX_DECK_SIZE = 52;
    static const int NUM_SUITS = 4;
    static const int NUM_RANKS = 13;

    Deck() : cards()
    {}
    void deckInitalization();
    void deckShuffle();
    std::vector<Card> cards;

};
