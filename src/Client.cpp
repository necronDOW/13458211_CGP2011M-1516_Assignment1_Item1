#include "Client.h"
#include "MenuManager.h"
#include "SceneManager.h"

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
		online = false;
		Quit();
	}
	else
	{
		std::cout << "Connection established successfully (" << ip << ").\n" << std::endl;
		SDLNet_TCP_AddSocket(server, connection);
		online = true;
	}
}

Client::~Client()
{
	if (connection != NULL)
		SDLNet_TCP_Send(connection, "2*\n", 4);
	Quit();
}

void Client::SendMessage(char* flag, char* msg)
{
	if (online)
	{
		char* fullMsg = StrLib::str_concat(std::vector<char*> { flag, "*", msg });
		SDLNet_TCP_Send(connection, fullMsg, strlen(fullMsg + 1));
	}
}

void Client::CheckIncoming(Game* game)
{
	if (online && SDLNet_CheckSockets(server, 0) > 0)
	{
		char temp[1400];

		if (SDLNet_SocketReady(connection))
		{
			SDLNet_TCP_Recv(connection, temp, 1400);

			int commandID = GetCommandID(temp);
			switch (commandID)
			{
				case 0:
					std::cout << "Connected to server (" << ip.host << ") successfully." << std::endl;
					game->GetMenuManager()->SetActiveMenu(game->GetMenuManager()->FindMenuByTag("load"));
					break;

				case 1:
					game->GetSceneManager()->UpdateSceneObject(StrLib::str_split(temp, "*")[1]);
					break;

				case 2:
					std::cout << "Player " << StrLib::str_split(temp, "*")[1] << " disconnected." << std::endl;
					break;

				case 3:
					std::cout << "Unable to connect to server (" << ip.host << "), too many players." << std::endl;
					Quit();
					break;

				case 4:
					std::cout << "Timed out, disconnected from server (" << ip.host << ")." << std::endl;
					game->SetGameState("play");
					Quit();
					break;

				case 5:
					game->SetGameState("play");
					break;
			}
		}
	}
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

	clientID = -1;
	online = false;
}

int Client::GetCommandID(char* msg)
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

int Client::GetClientID() { return clientID; }