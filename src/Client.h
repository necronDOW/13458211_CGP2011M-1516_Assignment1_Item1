#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <SDL.h>
#include <SDL_net.h>

/* Reference:
	Name: "FPS game (OpenGL,SDL,C++) tutorial 12 - multiplayer, networking, server".
	Author: thscplusplusguy (Youtube).
	Link: https://www.youtube.com/watch?v=iJfC4-yNnzY */

class Client
{
	public:
		Client();
		Client(const char* ip);
		~Client();

		bool IsOnline();

	private:
		void Quit();

		IPaddress ip;
		SDLNet_SocketSet server;
		TCPsocket connection;
		char message[1400];
		bool online;
};

#endif