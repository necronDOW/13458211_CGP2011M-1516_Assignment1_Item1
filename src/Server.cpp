#include "Server.h"

Server::Server(int maxPlayers)
{
	if (SDLNet_Init() != 0)
	{
		std::cout << "Error when instantiating SDL_net (SDLNet_Init)." << std::endl;
		Quit();
	}
	std::cout << "SDL_net initialized successfully." << std::endl;

	online = true;
	this->maxPlayers = maxPlayers;

	SDLNet_ResolveHost(&ip, NULL, 1234);
	server = SDLNet_TCP_Open(&ip);
	sockets = SDLNet_AllocSocketSet(maxPlayers);
	CalculateAvailableIDs();

	playerCount++;
	GetAvailableID();
}

Server::~Server()
{
	Quit();
}

void Server::CheckIncoming()
{
	if (online)
	{
		// Check for new connection requests.
		char temp[1400];
		TCPsocket tmpSocket = SDLNet_TCP_Accept(server);

		if (tmpSocket)
		{
			if (playerCount < maxPlayers)
				AddSocket(tmpSocket, temp);
			else sprintf(temp, "3*\n");

			SDLNet_TCP_Send(tmpSocket, temp, strlen(temp) + 1);
		}

		// Check for incoming messages from existing connections.
		while (SDLNet_CheckSockets(sockets, 0) > 0)
		{
			for (unsigned int i = 0; i < playerCount - 1; i++)
				InterpretIncoming(i, socketVector[i], temp);
		}

		// Disconnect players due to timeout.
		for (unsigned int i = 0; i < playerCount - 1; i++)
		{
			if (SDL_GetTicks() - socketVector[i].timeout > 10000)
			{
				sprintf(temp, "2*%d\n", socketVector[i].id);
				CirculateMsg(i, temp);

				SDLNet_TCP_Send(socketVector[i].socket, "4*\n", 3);
				RemoveSocket(i);
			}
		}
	}
}

void Server::Quit()
{
	for (data s : socketVector)
		SDLNet_TCP_Close(s.socket);

	SDLNet_FreeSocketSet(sockets);
	SDLNet_TCP_Close(server);
	SDLNet_Quit();
}

void Server::AddSocket(TCPsocket newSocket, char* str)
{
	int id = GetAvailableID();

	SDLNet_TCP_AddSocket(sockets, newSocket);
	socketVector.push_back(data(newSocket, SDL_GetTicks(), id));
	playerCount++;
	sprintf(str, "0*%d\n", id);


	std::cout << "Player Connected: " << id << "." << std::endl;
}

void Server::RemoveSocket(int index)
{
	SDLNet_TCP_DelSocket(sockets, socketVector[index].socket);
	SDLNet_TCP_Close(socketVector[index].socket);
	socketVector.erase(socketVector.begin() + index);
	CalculateAvailableIDs();

	std::cout << "Player Disconnected: " << playerCount-- << "." << std::endl;
}

void Server::InterpretIncoming(int index, data &incoming, char* str)
{
	if (SDLNet_SocketReady(incoming.socket))
	{
		incoming.timeout = SDL_GetTicks();

		SDLNet_TCP_Recv(incoming.socket, str, 1400);

		int commandID = GetCommandID(str);
		switch (commandID)
		{
			case 1:
				CirculateMsg(index, str);
				break;
			case 2:
				CirculateMsg(index, str);
				RemoveSocket(index);
				break;
		}
	}
}

void Server::CirculateMsg(int originIndex, char* str)
{
	for (unsigned int i = 0; i < playerCount - 1; i++)
	{
		if (i == originIndex)
			continue;
		SDLNet_TCP_Send(socketVector[i].socket, str, strlen(str + 1));
	}
}

int Server::GetCommandID(char* msg)
{
	int commandID = msg[0] - '0';
	int i = 1;

	while (msg[i] >= '0' && msg[i] <= '9')
	{
		commandID *= 10;
		commandID += msg[i] - '0';
		i++;
	}

	return commandID;
}

void Server::CalculateAvailableIDs()
{
	availableIDs.clear();

	if (socketVector.size() == maxPlayers)
		return;

	for (unsigned int i = 1; i <= maxPlayers; i++)
	{
		bool available = true;

		for (unsigned int j = 0; j < socketVector.size(); j++)
		{
			if (socketVector[j].id == i)
			{
				available = false;
				break;
			}
		}

		if (available)
			availableIDs.push_back(i);
	}
}

int Server::GetAvailableID()
{
	if (availableIDs.size() > 0)
	{
		int id = availableIDs[0];
		availableIDs.erase(availableIDs.begin());

		return id;
	}

	return -1;
}

int Server::GetPlayerCount() { return playerCount; }