#include "Server.h"

sf::Packet& operator<<(sf::Packet& packet, const sf::Vector2f& vec)
{
    return packet << vec.x << vec.y;
}

sf::Packet& operator>>(sf::Packet& packet, sf::Vector2f& vec)
{
    return packet >> vec.x >> vec.y;
}

sf::Packet& operator<<(sf::Packet& packet, const Transform& transform)
{
    return packet << transform.position << transform.velocity << transform.scale << transform.rotation;
}

sf::Packet& operator>>(sf::Packet& packet, Transform& transform)
{
    return packet >> transform.position >> transform.velocity >> transform.scale >> transform.rotation;
}

Server::Server()
{
    running = true;

    if (listener.listen(4500) == sf::Socket::Done)
        std::cout << "Started listening on port " << listener.getLocalPort() << "\n";
    else
    {
        if (listener.listen(sf::Socket::AnyPort) == sf::Socket::Done)
            std::cout << "Failed to listen on port 4500, listening on port " << listener.getLocalPort() << "\n";
    }

    players[0].transform.position = {10, 250};
    players[0].transform.velocity = {0, 0};
    players[0].transform.scale = {1, 1};
    players[0].transform.rotation = 0;
    players[0].score = 0, players[0].ID = 0;

    players[1].transform.position = {780, 250};
    players[1].transform.velocity = {0, 0};
    players[1].transform.scale = {1, 1};
    players[1].transform.rotation = 0;
    players[1].score = 0, players[0].ID = 1;
}

Server::~Server()
= default;

void Server::run()
{
    while (running)
    {

    }
}
