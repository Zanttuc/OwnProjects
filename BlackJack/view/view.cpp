#include "view.h"
#include "../controller.h"

std::string ViewInterface::cardValue(const Card card)
{
    std::string value = "";
    switch(card.rank)
    {
    case ACE:
        value = "A";
        break;
    case TWO:
    case THREE:
    case FOUR:
    case FIVE:
    case SIX:
    case SEVEN:
    case EIGHT:
    case NINE:
    case TEN:
        value = std::to_string(card.rank);
        break;
    case JACK:
        value = "J";
        break;
    case QUEEN:
        value = "Q";
        break;
    case KING:
        value = "K";
        break;
    }

    switch(card.suit)
    {
    case SPADES:
        value += " of SPADES";
        break;
    case HEARTS:
        value += " of HEARTS";
        break;
    case DIAMONDS:
        value += " of DIAMONDS";
        break;
    case CLUBS:
        value += " of CLUBS";
        break;
    }

    return value;
}

void View::printHand(const Player player)
{
    std::cout << "\n" << player.name << " hand is: " << std::endl;
    for (const Card& c : player.hand)
    {
        std::cout << cardValue(c) << std::endl;
    }
    std::cout << '\n' << player.handValue << " in total\n" << std::endl;
}

void View::printStatus(const Player player)
{
    wait();
    switch(player.status)
    {
    case DEFAULT:
        std::cout << "Something went wrong with " << player.name << std::endl;
        break;
    case WIN:
        std::cout << player.name << ": Player wins!" << std::endl;
        break;
    case LOSE:
        std::cout << player.name << ": Player loses!" << std::endl;
        break;
    case BUSTED:
        std::cout << player.name << ": Player bust!" << std::endl;
        break;
    case DRAW:
        std::cout << player.name << ": It's a draw!" << std::endl;
        break;
    }
}

void View::printTurn(const std::string name)
{
    wait();
    std::cout << name << " turn!" << std::endl;
    for(int i = 0; i < 20; ++i)
    {
        std::cout << '-';
    }
}

int View::readPlayerCount()
{
    int count = 0;
    std::cout << "How many players?" << std::endl;
    std::cin >> count;
    return count;
}

int View::readPlayerAction()
{
    int action = 0;
    std::cout << "What would you like to do? 1 = HIT, 2 = STAND" << std::endl;
    std::cin >> action;
    return action;
}

void View::wait()
{
    for (int i = 0; i < 25; ++i)
    {
        std::cout << "- ";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout << std::endl;
}
