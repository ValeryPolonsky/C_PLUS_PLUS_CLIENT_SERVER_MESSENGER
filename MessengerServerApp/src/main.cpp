#include <iostream>
#include "TCPMessengerServer.h"
using namespace std;

void printHelpMenu();

int main()
{
	TCPMessengerServer* msngrServer = new TCPMessengerServer();
	bool loop = true;
	while(loop)
	{
		string msg;
		string roomName;
		string command;

		printHelpMenu();

		cin >> command;
		if(command=="lu"){
			msngrServer->getLogin()->printAllUsers();
		}
		else if(command == "lcu")
		{
			msngrServer->getLogin()->getDispatcher()->printConnectedUsers();
		}
		else if(command == "lr")
		{
			msngrServer->getLogin()->getDispatcher()->printAllRooms();
		}
		else if(command == "ls")
		{
			msngrServer->getLogin()->getDispatcher()->printAllSessions();
		}
		else if(command == "lru")
		{
			cin >> roomName;
			msngrServer->getLogin()->getDispatcher()->printAllUserInRoom(roomName);
		}
		else if(command == "h")
		{
			printHelpMenu();
		}
		else if(command == "x")
		{
			loop = false;
		}
		else
		{
			cout << "Wrong input" << endl;
		}
	}
	msngrServer->close();
	delete msngrServer;
	cout << "Messenger was closed" << endl;

	return 0;
}

void printHelpMenu()
{
	cout << "*****************************************************" << endl;
	cout << "********************* MAIN MENU *********************" << endl;
	cout << "*** List all users              : lu              ***" << endl;
	cout << "*** List all connected users    : lcu             ***" << endl;
	cout << "*** List all sessions           : ls              ***" << endl;
	cout << "*** List all rooms              : lr              ***" << endl;
	cout << "*** List all users in this room : lru <room name> ***" << endl;
	cout << "*** Shutdown                    : x               ***" << endl;
	cout << "*****************************************************" << endl;
	cout << "*****************************************************" << endl;
}
