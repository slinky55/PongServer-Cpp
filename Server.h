#pragma once

#include <iostream>

#include <SFML/Network.hpp>

#include "Player.h"

class Server
{
public:
    Server();
    ~Server();

    void run();
private:
    sf::Uint32 playerCount = 0;

    bool running;

    sf::TcpListener listener;
    sf::SocketSelector selector;

    Player players[2];

    struct Ball
    {
        sf::Transform transform;
    } ball;
};
