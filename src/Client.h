#ifndef CLIENT_H
#define CLIENT_H

// C++ includes
#include <iostream>

// Project includes
#include "Game.h"

// SDL includes
#include <SDL.h>
#include <SDL_net.h>

/* Reference:
	Name: "FPS game (OpenGL,SDL,C++) tutorial 12 - multiplayer, networking, server".
	Author: thscplusplusguy (Youtube).
	Link: https://www.youtube.com/watch?v=iJfC4-yNnzY */

class Client
{
	public:
		/* Client 
			ip : The target server ip address. */
		Client(const char* ip);

		/* Client
			** Default Destructor ** */
		~Client();

		/* Send a message to the server. 
			flag : Message flag, should be a number. 
			msg : The desired message to send, like serialized data. */
		void SendMessage(char* flag, char* msg);

		/* Check for any incoming messages from the server. 
			game : Reference to the game. */
		void CheckIncoming(Game* game);

		/* Bool that represents whether the client is online or not. */
		bool IsOnline();

		/* Quit logic for this client, cleans up any pointers. */
		void Quit();

		/* Returns the ID of this client. */
		int GetClientID();

	private:
		/* Resolve the command ID based on the first character of a message. 
			msg : The message which requires identification. */
		int GetCommandID(char* msg);

		IPaddress ip;				// The ip address of the server.
		SDLNet_SocketSet server;	// Socket set for the connected server.
		TCPsocket connection;		// A TCPsocket which represents the connection between client and server.
		bool online;				// The clients online status.
		int clientID = -1;			// The id for this client as allocated by the server (related to player number).
};

#endif