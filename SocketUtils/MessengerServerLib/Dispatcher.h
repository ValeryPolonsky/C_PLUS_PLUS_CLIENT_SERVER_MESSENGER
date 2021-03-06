#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <strings.h>
#include <string.h>
#include <map>
#include <vector>
#include "MThread.h"
#include "TCPSocket.h"
#include<iostream>
#include<fstream>
#include "TCPMessengerProtocol.h"
#include "UDPSocket.h"
#include "User.h"
#include "Room.h"
#include "MultiThreadLocker.h"

using namespace std;

class Dispatcher : MThread
{
	bool running;
	typedef map <string , User > UsersMap;
    UsersMap users;
    typedef map <string , string > Sessions;
    Sessions sessions;
    typedef map<string ,Room > RoomsMap;
    RoomsMap rooms;
    typedef map<string , TCPSocket *> LoggedIn;
    LoggedIn* connected;
    MultiThreadLocker* multiThreadLocker;
    map <string, string > *  loggedIn;

public:

      /*
     * Constructor - creates a new dispatcher with given users map
     */
	Dispatcher(map<string , TCPSocket *> * mapi , map <string , string > *logedin);

	/*
	 * Sends users from the map
	 */
	void sendUsersFromMap(TCPSocket * p);

	/*
	 * Returns length of users map
	 */
	int objectlength();

	/*
	 * Displays connected users
	 */
	void printConnectedUsers();

	/*
	 * Adds user to the users map
	 */
	void addUser(string name , TCPSocket * p);

	/*
	 * Searches user in users map by his name
	 */
	User* UserSearch(string Name);

	/*
	 * Searches user by socket in users map
	 */
	string searchByUser(TCPSocket* user);
	//TCPSocket* FindSocket(TCPSocket * P , string Address );
	//string AddressSearch(string Address);
	/*
	 * Searches user by his IP address
	 */
	string SearchByIp(string Ip);

	/*
	 * Searches room by it's name in the rooms map
	 */
	Room* FindByNameRoom(string roomName);

	/*
	 * Searches room by it's name in the rooms map
	 */
	void printAllUserInRoom(string room_name);

	/*
	 * Prints all users that are connected to the room
	 */
	void printVector(vector<User> vec);
	/*
	 * Updates users details after connection
	 */
	bool updateUsersAfterConnection(vector<User  > vec, int Command , string Data );

	/*
	 * Sends room name through given socket
	 */
	void sendRoomsName(TCPSocket * p);

	/*
	 * Returns number of users in the given vector
	 */
	int getNumberOfUsers(vector<User> vec);
	/*
	 * Returns number of users that are connected to the room
	 */
	int rooms_length();

	/*
	 * Sends error status
	 */
	bool sendErrorstatus(TCPSocket * sock , User * user  , int Command);

	/*
	 * Sends users that are connected to room
	 */
	void sendUsersFromRoom(TCPSocket * sock , vector<User > vec);

	/*
	 * Deletes user from the room
	 */
	bool eraseFromRoom(string user , Room * cr );

	/*
	 * Checks if the given user is the owner
	 */
	bool checkWhoIsOwner(string owner , string user);

	/*
	 * Displays all created rooms
	 */
	void printAllRooms();

	/*
	 * Closes session with peer
	 */
	void closeSessionWithPeer(TCPSocket * readypeer );

	/*
	 * Checks if the user exists in the room
	 */
	bool isExistRoom(string room_name);

	/*
	 * Deletes room session in all users in the room
	 */
    void eraseSessionStatusfromAllUsersInRoom(vector<User > vec);

    /*
     * Prints all opened sessions
     */
    void printAllSessions();

    /*
     * Closes a specific room
     */
    void closeRoom(TCPSocket * readypeer);

    /*
     * Finds user in users map and creates session with him if he's not busy or not connected
     */
    void createSessionWithPeer(TCPSocket * readypeer , int Command);

    /*
     * Prints users list
     */
    void printUserList(TCPSocket * readypeer , int Command);

    /*
     * Prints status that user is connected
     */
    void userConnected(TCPSocket * readypeer , int Command);

    /*
     * Returns status of the user
     */
    void getStatus(TCPSocket * readypeer , int Command);

    /*
     * Opens a new chat room
     */
    void openRoom(TCPSocket * readypeer , int Command);
    /*
     * Joins the user to the chat room
     */
    void joinRoom(TCPSocket * readypeer,int Command);

    /*
     * Displays all created chat rooms
     */
    void displayAllRooms(TCPSocket * readypeer,int Command);

    /*
     * Displays all users in chat room
     */
    void printRoomsUsers(TCPSocket * readypeer , int Command);

    /*
     * Disconnects the user from the specific room
     */
    void exitFromRoom(TCPSocket * readypeer , int Command);

    /*
     * Disconnects users from server
     */
    void disconnectFromServer(TCPSocket * readypeer , int Command);

    /*
     * Starts dispatcher thread
     */
	void run();

	/*
	 * Destructor
	 */
	virtual ~Dispatcher();
};


#endif
