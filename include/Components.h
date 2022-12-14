#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/TcpSocket.hpp>

struct Transform
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f scale;
    float rotation = 0;
};

struct Connection
{
    sf::IpAddress playerIp {sf::IpAddress::LocalHost};
    unsigned short playerPort = 4500;
    sf::UdpSocket socket;
};