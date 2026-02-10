#pragma once
#include <vector>
#include <chrono>
#include <thread>

class Player;
struct Card;

class ViewInterface
{
public:
    ViewInterface()
    {}
    virtual ~ViewInterface(){}
    virtual void printHand(const Player player) = 0;
    virtual void printStatus(const Player player) = 0;
    virtual void printTurn(const std::string name) = 0;
    virtual void wait() = 0;
    virtual int readPlayerCount() = 0;
    virtual int readPlayerAction() = 0;
    std::string cardValue(const Card card);
};

class View : public ViewInterface
{
public:
    View()
    {}
    ~View(){}
    virtual void printHand(const Player player) override;
    virtual void printStatus(const Player player) override;
    virtual void printTurn(const std::string name) override;
    virtual void wait() override;
    virtual int readPlayerCount() override;
    virtual int readPlayerAction() override;
};
