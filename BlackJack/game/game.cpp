#include "game.h"
#include <random>

void Game::initializeGameDeck()
{
    gameDeck.clear();
    for (int i = 0; i < amountOfDecks; ++i)
    {
        Deck deck;
        deck.deckInitalization();
        gameDeck.insert(gameDeck.end(), deck.cards.begin(), deck.cards.end());
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(gameDeck.begin(), gameDeck.end(), g);
}

void Game::initializePlayers()
{
    for (int i = 0; i < amountOfPlayers; ++i)
    {
        Player player("Player " + std::to_string(i + 1));
        gamePlayers.push_back(player);
    }
}

void Game::initialDeal()
{
    for (int i = 0; i < amountOfPlayers; ++i)
    {
        dealPlayer(i);
    }
    dealDealer();
    for (int i = 0; i < amountOfPlayers; ++i)
    {
        dealPlayer(i);
    }
}

void Game::checkRemainingDeck()
{
    if (gameDeck.size() <= cardsLeft)
    {
        initializeGameDeck();
    }
}

void Game::updateValue(std::vector<Card> hand, Player& player)
{
    player.handValue = 0;
    size_t card = 0;
    std::sort(hand.begin(), hand.end(),[](const Card& card1, const Card& card2){return card1.rank > card2.rank;});
    for (const Card& c : hand)
    {
        ++card;
        switch(c.rank)
        {
        case ACE:
            if (card == hand.size())
            {
                if (player.handValue < 11)
                {
                    player.handValue += 11;
                    continue;
                }
            }
            player.handValue += 1;
            break;
        case JACK:
        case QUEEN:
        case KING:
            player.handValue += 10;
            break;
        default:
            player.handValue += c.rank;
            break;
        }
    }
}

void Game::dealerAction()
{
    while(dealer.handValue < dealer.MAX_DRAW)
    {
        dealDealer();
        if (dealer.handValue >= dealer.BUST)
        {
            dealer.status = BUSTED;
        }
    }
}

int Game::getAmountPlayers()
{
    return amountOfPlayers;
}

Player& Game::getPlayer(int playerNum)
{
    return gamePlayers[playerNum];
}

const Dealer Game::getDealer()
{
    return dealer;
}

const std::vector<Card> Game::getDealerHand()
{
    return dealer.hand;
}

const Card& Game::dealPlayer(const int playerNum)
{
    checkRemainingDeck();
    const Card& card = gameDeck.front();
    gamePlayers[playerNum].hand.push_back(card);
    gameDeck.erase(gameDeck.begin());
    updateValue(gamePlayers[playerNum].hand, gamePlayers[playerNum]);
    return card;
}

const Card& Game::dealDealer()
{
    checkRemainingDeck();
    const Card& card = gameDeck.front();
    dealer.hand.push_back(card);
    gameDeck.erase(gameDeck.begin());
    updateValue(dealer.hand, dealer);
    return card;
}

Status Game::checkWin(const int p_hand, const int d_hand)
{
    if (p_hand > 21)
    {
        return BUSTED;
    }
    else if (d_hand > 21)
    {
        return WIN;
    }
    else
    {
        if (p_hand > d_hand)
        {
            return WIN;
        }
        else if (p_hand < d_hand)
        {
            return LOSE;
        }
        else
        {
            return DRAW;
        }
    }
}
