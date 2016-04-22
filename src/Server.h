#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_net.h>

/* Reference:
	Name: "FPS game (OpenGL,SDL,C++) tutorial 12 - multiplayer, networking, server".
	Author: thscplusplusguy (Youtube).
	Link: https://www.youtube.com/watch?v=iJfC4-yNnzY */

class Server
{
	struct data
	{
		TCPsocket socket;
		unsigned int timeout;
		int id;

		data(TCPsocket s, unsigned int t, int i)
			: socket(s), timeout(t), id(i) { }
	};

	public:
		Server();
		Server(int maxPlayers);
		~Server();
		void CheckIncoming();
		void Quit();

		bool online = false;

	private:
		void AddSocket(TCPsocket newSocket, char* str);
		void RemoveSocket(int index);
		void InterpretIncoming(int index, data &incoming, char* str);
		void CirculateMsg(int originIndex, char* str);
		int GetCommandID(char* msg);

		int currentID = 0, playerCount = 0, maxPlayers;
		TCPsocket server;
		IPaddress ip;
		std::vector<data> socketVector;
		SDLNet_SocketSet sockets;
};

#endif