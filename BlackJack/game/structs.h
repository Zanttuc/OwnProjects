#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

enum Rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
enum Suit { SPADES, HEARTS, DIAMONDS, CLUBS };
enum Status { DEFAULT, WIN, LOSE, BUSTED, DRAW };
enum Action { HIT = 1, STAND };

struct Card {
    Rank rank;
    Suit suit;
};
