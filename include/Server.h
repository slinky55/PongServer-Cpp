#pragma once

#include <iostream>

#include <SFML/Network.hpp>

#include "Player.h"

class Server
{
public:
    Server();
    ~Server();

    void init();
    void run();
private:
    sf::Uint32 currentID {0};

    bool running;

    sf::UdpSocket socket;
    sf::Clock clock;

    Player players[2];
    struct Ball
    {
        Transform transform;
    } ball;

    void update();
    void simulate(float dt);
    void receive();
    void broadcast();
};
