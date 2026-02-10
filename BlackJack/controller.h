#pragma once
#include "game/game.h"
#include "view/view.h"

bool checkInput(const std::string& arg);

class Controller
{
public:
    Controller(std::unique_ptr<Game>&& game, std::unique_ptr<ViewInterface>&& view)
        : m_game(std::move(game)), m_view(std::move(view))
    {}
    void play();


protected:
    std::unique_ptr<Game> m_game;
    std::unique_ptr<ViewInterface> m_view;

    void playerAction();
    void dealerAction();
    void getStatus();

};
