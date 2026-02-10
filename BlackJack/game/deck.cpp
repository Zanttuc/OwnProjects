#include "deck.h"
#include <random>

void Deck::deckInitalization()
{
    for (int suits = 0; suits < NUM_SUITS; ++suits)
    {
        for (int ranks = 1; ranks < NUM_RANKS+1; ++ranks)
        {
            Card card;
            card.suit = Suit(suits);
            card.rank = Rank(ranks);
            cards.push_back(card);
        }
    }
}

void Deck::deckShuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}
