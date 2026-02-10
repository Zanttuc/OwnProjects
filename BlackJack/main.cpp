#include "controller.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int amountOfDecks = 0;
    if (argc == 2)
    {
        std::string arg = argv[1];
        if (checkInput(arg))
        {
            amountOfDecks = std::stoi(argv[1]);
        }
    }
    else
    {
        std::cout << "Command line input was not valid. "
                  << "Deck amount is 4." << std::endl;
        amountOfDecks = 4;
    }

    auto view_2 = std::make_unique<View>();
    int amountOfPlayers = view_2->readPlayerCount();

    auto game = std::make_unique<Game>(amountOfDecks, amountOfPlayers);
    Controller play_2(std::move(game), std::move(view_2));
    play_2.play();

    return 0;
}
