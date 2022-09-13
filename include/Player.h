#pragma once

#include <SFML/Graphics.hpp>
#include <Components.h>

struct Player
{
    Transform transform;
    Connection connection;
    sf::Uint32 ID {0};
    sf::Uint32 score {0};
};


