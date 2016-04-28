#include "Client.h"

// Project includes
#include "MenuManager.h"
#include "SceneManager.h"

Client::Client(const char* ip)
{
	// Allocate necessary number of sockets for the server, just 1.
	server = SDLNet_AllocSocketSet(1);

	// Run all initialization logic, relaying any errors and quiting on failure.
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

	// Attempt to open a connection between this client and the server.
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
	// Inform the server that the client has disconnected and run clean up logic.
	if (connection != NULL)
		SDLNet_TCP_Send(connection, "2*\n", 4);
	Quit();
}

void Client::SendMessage(char* flag, char* msg)
{
	// If the client is online, concat (flag + msg) and send to the server.
	if (online)
	{
		char* fullMsg = StrLib::str_concat(std::vector<char*> { flag, "*", msg, "\n" });
		SDLNet_TCP_Send(connection, fullMsg, strlen(fullMsg + 1));
	}
}

void Client::CheckIncoming(Game* game)
{
	// Check for incoming information if online and a connection is established.
	if (online && SDLNet_CheckSockets(server, 0) > 0)
	{
		// Temporary char array to store message information.
		char temp[1400];

		// If the server has send any information.
		if (SDLNet_SocketReady(connection))
		{
			// Decode the information and take appropriate action based upon the message flag.
			SDLNet_TCP_Recv(connection, temp, 1400);
			std::vector<char*> messages;

			int commandID = GetCommandID(temp);
			switch (commandID)
			{
				case 0:
					// Connection successful.
					std::cout << "Connected to server (" << ip.host << ") successfully." << std::endl;
					game->GetMenuManager()->SetActiveMenu(game->GetMenuManager()->FindMenuByTag("load"));
					clientID = atoi(StrLib::str_split(temp, "*")[1]);
					break;

				case 1:
					// Update all functional scene elements with new information.
					messages = StrLib::str_split(temp, "*");

					for (int i = 1; i < messages.size(); i++)
					{
						char* tmp = StrLib::str_split(messages[i], " ")[0];
						game->GetSceneManager()->UpdateSceneObject(tmp);
					}
					break;

				case 2:
					// Player disconnected from server.
					std::cout << "Player " << StrLib::str_split(temp, "*")[1] << " disconnected." << std::endl;
					break;

				case 3:
					// Connection refused.
					std::cout << "Unable to connect to server (" << ip.host << "), too many players." << std::endl;
					Quit();
					break;

				case 4:
					// Timed out.
					std::cout << "Timed out, disconnected from server (" << ip.host << ")." << std::endl;
					game->SetGameState("play");
					Quit();
					break;

				case 5:
					// Play the game once the server is ready.
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
	// Close connection and free any necessary variables.
	SDLNet_TCP_Close(connection);
	SDLNet_FreeSocketSet(server);
	SDLNet_Quit();

	// Set clientID to -1 and online to false.
	clientID = -1;
	online = false;
}

int Client::GetCommandID(char* msg)
{
	// Resolve a command flag from the given message.
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