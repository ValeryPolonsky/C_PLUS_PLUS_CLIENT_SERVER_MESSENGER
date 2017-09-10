#ifndef USER_CPP_
#define USER_CPP_

#include "User.h"
#include "TCPSocket.h"

using namespace std;

/*
 * Constructor - creates a new user
 */
User::User(string userName  , TCPSocket* p) : TCPSocket(p)
{
	name=userName;
	session="OUT";
	chat_room="NONE";
}

/*
 * Returns user's name
 */
string User::getName()
{
	return name;
}

/*
 * Returns session status of the user
 */
string User::getStatus()
{
	return session;
}

/*
 * Deletes user
 */
User::~User() {

}

/*
 * Sets user's status to - out of session
 */
void User::eraseSessionStatus()
{
	this->session = "OUT";
}

/*
 * Sets a given room to the chat room status
 */
void User::setRoom(string room)
{
	chat_room = room;
}

/*
 * Returns status of the chat room
 */
string User::getRoom()
{
	return this->chat_room;
}

/*
 * Sets session status of the room
 */
void User::setSessionStatus()
{
	this->session="IN";
}



#endif /* USER_H_ */
