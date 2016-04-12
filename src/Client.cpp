#include "Client.h"

Client::Client()
{
	online = false;
}

Client::Client(const char* ip)
{
	server = SDLNet_AllocSocketSet(1);

	if (SDLNet_Init() != 0)
	{
		std::cout << "Error when instantiating SDL_net (SDLNet_Init).\n" << std::endl;
		Quit();
	}
	std::cout << "SDL_net initialized successfully." << std::endl;

	if (SDLNet_ResolveHost(&this->ip, ip, 1234) == -1)
	{
		std::cout << "There was a problem when connecting IP " << ip << " to the server.\n" << std::endl;
		Quit();
	}

	connection = SDLNet_TCP_Open(&this->ip);
	if (connection == NULL)
	{
		std::cout << "Error: Bad server IP address (" << ip << "), connection aborted.\n" << std::endl;
		Quit();
	}
	else
	{
		SDLNet_TCP_AddSocket(server, connection);
		online = true;

		std::cout << "Connection established successfully (" << ip << ").\n" << std::endl;
	}
}

Client::~Client()
{
	if (connection != NULL)
		SDLNet_TCP_Send(connection, "2 \n", 4);
	Quit();
}

bool Client::IsOnline()
{
	return online;
}

void Client::Quit()
{
	SDLNet_TCP_Close(connection);
	SDLNet_FreeSocketSet(server);
	SDLNet_Quit();

	online = false;
}