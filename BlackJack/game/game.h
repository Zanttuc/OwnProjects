#pragma once
#include "player.h"

class Game {
public:
    Game(const int decks, const int players)
        : amountOfDecks(decks), amountOfPlayers(players),
          cardsLeft(30), gamePlayers(), gameDeck(), dealer()
    {}
    void initializeGameDeck();
    void initializePlayers();
    void initialDeal();
    void checkRemainingDeck();
    void updateValue(std::vector<Card> hand, Player& player);
    void dealerAction();
    int getAmountPlayers();
    Player& getPlayer(int playerNum);
    const Dealer getDealer();
    const std::vector<Card> getDealerHand();
    const Card& dealPlayer(const int playerNum);
    const Card& dealDealer();
    Status checkWin(const int p_hand, const int d_hand);

protected:      //Still not working
    const int amountOfDecks;
    const int amountOfPlayers;
    const size_t cardsLeft;
    std::vector<Player> gamePlayers;
    std::vector<Card> gameDeck;
    Dealer dealer;
};
