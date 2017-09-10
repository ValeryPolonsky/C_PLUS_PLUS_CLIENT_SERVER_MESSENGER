#ifndef CHATROOM_H_
#define CHATROOM_H_

#include <strings.h>
#include <string.h>
#include <map>
#include <vector>
#include "MThread.h"
#include "TCPSocket.h"
#include <iostream>
#include <fstream>
#include "TCPMessengerProtocol.h"
#include "User.h"
#include "MultiThreadLocker.h"

using namespace std;
class  User;
class Room {
	string name;
	string owner;
	MultiThreadLocker* multiThreadLocker;
    vector<User  > users;

public:
    /*
     * Constructor - creates a new chat room
     */
	Room();

	/*
	 * Constructor - initializes all data members
	 */
	Room(string name , string owner , User  user);

	/*
	 * Adds user to the room
	 */
	void setUser(User  User);

	/*
	 * Returns owner of the room
	 */
	string getOwner();

	/*
	 * Erases user from the chat room
	 */
	bool eraseUser(string user_name);

	/*
	 * Returns users that are connected to the room
	 */
	vector<User> getUserList();

	/*
	 * Destructor - deletes room
	 */
	virtual ~Room();
};


#endif
