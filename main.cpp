#include <iostream>
#include <SFML/Network.hpp>

int main()
{
	std::cout << "Starting Server...\n";

    sf::TcpListener listener;

    if (listener.listen(53000) != sf::Socket::Done)
    {
        std::cout << "Failed to listen on port 53000\n";
        return -1;
    }

    sf::TcpSocket client;
    if (listener.accept(client) != sf::Socket::Done)
    {
        std::cout << "Failed to establish connection with client\n";
        return -1;
    }

    std::cout << "Client " << client.getRemoteAddress()->toString() << " Connected!\n";

    char data[5];
    size_t received {0};

    if (client.receive(data, 5, received) != sf::Socket::Done)
    {
        std::cout << "Failed to receive client data!\n";
        return -1;
    }

    std::cout << "Received " << received << " bytes!\n";

	return 0;
}
