#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include "Game.h"

#include <SDL.h>
#include <SDL_net.h>

/* Reference:
	Name: "FPS game (OpenGL,SDL,C++) tutorial 12 - multiplayer, networking, server".
	Author: thscplusplusguy (Youtube).
	Link: https://www.youtube.com/watch?v=iJfC4-yNnzY */

class Client
{
	public:
		Client(const char* ip);
		~Client();

		void SendMessage(char* flag, char* msg);
		void CheckIncoming(Game* game);
		bool IsOnline();

		int GetClientID();

	private:
		void Quit();
		int GetCommandID(char* msg);

		IPaddress ip;
		SDLNet_SocketSet server;
		TCPsocket connection;
		char message[1400];
		bool online;
		int clientID = -1;
};

#endif