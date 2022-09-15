#include <Server.h>

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
= default;

Server::~Server()
= default;

void Server::init()
{
    std::cout << "Starting server...\n";

    running = true;

    players[0].transform = {
        {10, 250},
        {0, 0},
        {1, 1},
        0
    };

    players[1].transform = {
        {780, 250},
        {0, 0},
        {1, 1},
        0
    };

    ball.transform = {
        {400, 300},
        {-100, 100},
        {1, 1},
        0
    };

    if (socket.bind(4500) != sf::Socket::Done)
    {
        std::cout << "Couldn't bind to port 4500\n";
        if (socket.bind(sf::Socket::AnyPort) == sf::Socket::Done)
        {
            std::cout << "Bound socket to port " << socket.getLocalPort() << "\n";
        }
    }
    else
    {
        std::cout << "Bound socket to port 4500\n";
    }
        
    socket.setBlocking(false);
}

void Server::run()
{
    std::cout << "Server started!\n";
    while (running)
    {
        receive();
        if (currentID == 2)
        {
            update();
            simulate(clock.restart().asSeconds());
            broadcast();
        }
    }
}

void Server::receive()
{
    sf::IpAddress senderIp;
    unsigned short senderPort;

    sf::Packet received;

    if (socket.receive(received, senderIp, senderPort) == sf::Socket::Done)
    {
        int signal;
        uint32_t senderID;
    
        received >> signal;

        sf::Packet out;

        switch (signal)
        {
            case 0:      // Connection signal
                if (currentID < 2)
                {
                    players[currentID].connection.playerIp = senderIp;
                    players[currentID].connection.playerPort = senderPort;
                    out << currentID << players[currentID].transform;
                    if (socket.send(out, senderIp, senderPort) == sf::Socket::Done)
                    {
                        std::cout << "Client connected at " << senderIp.toString() << "\n";
                        currentID++;
                    }
                }    
                if (currentID == 2)
                    clock.restart();
                break;
            case 1:     // Message signal
                received >> senderID;
                received >> players[senderID].cmd;
                break;
            case -1:    // Disconnect signal
                received >> senderID;
                std::cout << "Player at " << senderIp << " disconnected\n";
                currentID--;
                break;
        }
    }
}

void Server::update()
{
    for (auto& player : players)
    {
        if (player.cmd == 0)         // UP
            player.transform.velocity.y = -100;
        else if (player.cmd == 1)   // DOWN
            player.transform.velocity.y = 100;
        else if (player.cmd == -1)  // STOP
            player.transform.velocity.y = 0;
    }
}

void Server::simulate(float dt)
{
    for (auto& player : players)
        player.transform.position += (player.transform.velocity * dt);
    ball.transform.position += (ball.transform.velocity * dt);
}

void Server::broadcast()
{
    sf::Packet p1, p2;

    p1 << players[0].transform << players[1].transform << ball.transform;
    p2 << players[1].transform << players[0].transform << ball.transform;

    socket.send(p1, players[0].connection.playerIp, players[0].connection.playerPort);
    socket.send(p2, players[1].connection.playerIp, players[1].connection.playerPort);
}