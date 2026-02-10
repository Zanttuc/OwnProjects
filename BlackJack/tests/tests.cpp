#include "../game/game.h"
#include <gtest/gtest.h>

class GameFixture : public ::testing::Test
{
public:
    GameFixture() : m_game(4, 4)
    {
        m_game.initializePlayers();
        m_game.initializeGameDeck();
    }
protected:
    Game m_game;
};

class DealerFixture : public GameFixture
{
protected:
    DealerFixture()
    {}
    const int amountOfTests = 2'000;
};

TEST_F(GameFixture, Initializing)
{
    EXPECT_EQ(m_game.gameDeck.size(), (m_game.amountOfDecks * 52));
    EXPECT_EQ(m_game.gamePlayers.size(), m_game.amountOfPlayers);
}

TEST_F(GameFixture, Dealing)
{
    for (Player& p : m_game.gamePlayers)
    {
        m_game.dealHand(p);
        m_game.dealHand(p);
        EXPECT_EQ(p.hand.size(), 2);
    }
    EXPECT_EQ(m_game.gameDeck.size(),
              ((m_game.amountOfDecks * 52)-(m_game.amountOfPlayers * 2)));
}

TEST_F(GameFixture, HandValue)
{
    Player p1 = m_game.gamePlayers[1];

    p1.hand.clear();
    p1.hand = {{NINE, SPADES},
               {ACE, HEARTS},
               {ACE, DIAMONDS}};
    m_game.updateValue(p1.hand, p1);
    EXPECT_EQ(p1.handValue, 21);

    p1.hand.clear();
    p1.hand = {{ACE, SPADES},
               {TEN, HEARTS},
               {JACK, DIAMONDS}};
    m_game.updateValue(p1.hand, p1);
    EXPECT_EQ(p1.handValue, 21);

    p1.hand.clear();
    p1.hand = {{ACE, DIAMONDS},
               {QUEEN, HEARTS},
               {ACE, DIAMONDS}};
    m_game.updateValue(p1.hand, p1);
    EXPECT_EQ(p1.handValue, 12);

    p1.hand.clear();
    p1.hand = {{ACE, SPADES},
               {TWO, CLUBS},
               {NINE, DIAMONDS},
               {SEVEN, DIAMONDS}};
    m_game.updateValue(p1.hand, p1);
    EXPECT_EQ(p1.handValue, 19);

    p1.hand.clear();
    p1.hand = {{ACE, SPADES},
               {SIX, HEARTS},
               {ACE, HEARTS},
               {ACE, HEARTS},
               {ACE, HEARTS}};
    m_game.updateValue(p1.hand, p1);
    EXPECT_EQ(p1.handValue, 20);

    p1.hand.clear();
    p1.hand = {{ACE, SPADES},
               {TWO, HEARTS},
               {ACE, HEARTS},
               {TWO, HEARTS},
               {ACE, HEARTS},
               {TWO, SPADES},
               {ACE, DIAMONDS},
               {TWO, DIAMONDS},
               {ACE, CLUBS},
               {SEVEN, HEARTS}};
    m_game.updateValue(p1.hand, p1);
    EXPECT_EQ(p1.handValue, 20);

    p1.hand.clear();
    p1.hand = {{TEN, SPADES},
               {TWO, HEARTS},
               {TWO, HEARTS},
               {TWO, HEARTS},
               {FOUR, HEARTS}};
    m_game.updateValue(p1.hand, p1);
    EXPECT_EQ(p1.handValue, 20);

    p1.hand.clear();
    p1.hand = {{FIVE, SPADES},
               {SIX, HEARTS},
               {TWO, HEARTS},
               {THREE, HEARTS},
               {FIVE, HEARTS}};
    m_game.updateValue(p1.hand, p1);
    EXPECT_EQ(p1.handValue, 21);

    p1.hand.clear();
    p1.hand = {{SEVEN, SPADES},
               {TEN, HEARTS}};
    m_game.updateValue(p1.hand, p1);
    EXPECT_EQ(p1.handValue, 17);

    p1.hand.clear();
    p1.hand = {{QUEEN, SPADES},
               {JACK, HEARTS}};
    m_game.updateValue(p1.hand, p1);
    EXPECT_EQ(p1.handValue, 20);
}


TEST_F(DealerFixture, RandomAction)
{
    for (int i = 0; i < amountOfTests; ++i)
    {
        m_game.dealer.hand.clear();
        m_game.dealHand(m_game.dealer);
        m_game.dealerAction();
        EXPECT_TRUE(m_game.dealer.handValue >= m_game.dealer.MAX_DRAW);
        EXPECT_TRUE(m_game.dealer.handValue < m_game.dealer.BUST
                    || m_game.dealer.status == BUSTED);
    }
}

TEST_F(DealerFixture, ManualAction)
{
    //ManualTest 1
    m_game.dealer.hand.clear();
    m_game.dealer.hand = {{ACE, SPADES},
                          {TWO, DIAMONDS},
                          {FOUR, HEARTS}};
    m_game.updateValue(m_game.dealer.hand, m_game.dealer);
    m_game.dealerAction();
    EXPECT_EQ(m_game.dealer.hand.size(), 3);

    //ManualTest 2
    m_game.dealer.hand.clear();
    m_game.dealer.hand = {{ACE, SPADES},
                          {FIVE, DIAMONDS},
                          {TEN, HEARTS}};
    m_game.updateValue(m_game.dealer.hand, m_game.dealer);
    m_game.dealerAction();
    EXPECT_EQ(m_game.dealer.hand.size(), 4);

    //ManualTest 3
    m_game.dealer.hand.clear();
    m_game.dealer.hand = {{JACK, SPADES},
                          {ACE, DIAMONDS}};
    m_game.updateValue(m_game.dealer.hand, m_game.dealer);
    m_game.dealerAction();
    EXPECT_EQ(m_game.dealer.hand.size(), 2);

    //ManualTest 4
    m_game.dealer.hand.clear();
    m_game.dealer.hand = {{TEN, CLUBS},
                          {FIVE, SPADES},
                          {TWO, CLUBS}};
    m_game.updateValue(m_game.dealer.hand, m_game.dealer);
    m_game.dealerAction();
    EXPECT_EQ(m_game.dealer.hand.size(), 3);

    //ManualTest 5
    m_game.dealer.hand.clear();
    m_game.dealer.hand = {{TWO, SPADES},
                          {TWO, DIAMONDS},
                          {ACE, HEARTS},
                          {ACE, DIAMONDS},
                          {KING, DIAMONDS},
                          {ACE, HEARTS}};

    m_game.updateValue(m_game.dealer.hand, m_game.dealer);
    m_game.dealerAction();
    EXPECT_EQ(m_game.dealer.hand.size(), 6);

    //ManualTest 6
    m_game.dealer.hand.clear();
    m_game.dealer.hand = {{TWO, SPADES},
                          {TWO, DIAMONDS},
                          {ACE, HEARTS},
                          {ACE, DIAMONDS},
                          {KING, DIAMONDS}};
    m_game.updateValue(m_game.dealer.hand, m_game.dealer);
    m_game.dealerAction();
    EXPECT_EQ(m_game.dealer.hand.size(), 6);

    //ManualTest 7
    m_game.dealer.hand.clear();
    m_game.dealer.hand = {{TWO, SPADES},
                          {TWO, DIAMONDS},
                          {JACK, HEARTS},
                          {SEVEN, SPADES}};
    m_game.updateValue(m_game.dealer.hand, m_game.dealer);
    m_game.dealerAction();
    EXPECT_EQ(m_game.dealer.hand.size(), 4);
}
