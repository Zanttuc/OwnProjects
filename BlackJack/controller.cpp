#include "controller.h"

bool checkInput(const std::string& arg)
{
    for (const char& c : arg)
    {
        if (isdigit(c) == false)
        {
            return false;
        }
    }
    return true;
}

void Controller::play()
{
    m_game->initializeGameDeck();
    m_game->initializePlayers();

    m_game->initialDeal();
    playerAction();
    dealerAction();

    getStatus();
}

void Controller::playerAction()
{
    for (int i = 0; i < m_game->getAmountPlayers(); ++i)
    {
        Player& curPlayer = m_game->getPlayer(i);
        m_view->printTurn(curPlayer.name);
        m_view->printHand(m_game->getDealer());
        int action = 0;
        while(action != 2)
        {
            m_view->printHand(curPlayer);
            if (curPlayer.handValue < curPlayer.BUST)
            {
                action = m_view->readPlayerAction();
                switch(action)
                {
                case HIT:
                    m_game->dealPlayer(i);
                    break;
                case STAND:
                    break;
                }
            }
            else
            {
                curPlayer.status = BUSTED;
                m_view->printStatus(curPlayer);
                action = 2;
            }
        }
    }
}

void Controller::dealerAction()
{
    m_view->printTurn(m_game->getDealer().name);
    m_game->dealerAction();
    m_view->printHand(m_game->getDealer());
}

void Controller::getStatus()
{
    for (int i = 0; i < m_game->getAmountPlayers(); ++i)
    {
        m_game->getPlayer(i).status = m_game->
                checkWin(m_game->getPlayer(i).handValue,
                         m_game->getDealer().handValue);
        m_view->printStatus(m_game->getPlayer(i));
    }
}
