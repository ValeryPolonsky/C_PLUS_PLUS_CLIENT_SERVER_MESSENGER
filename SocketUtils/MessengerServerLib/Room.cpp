#include "Room.h"
#include "User.h"

using namespace std;

/*
 * Constructor - creates a new chat room
 */
Room::Room()
{
	multiThreadLocker = new MultiThreadLocker(1);
}

/*
 * Constructor - initializes all data members
 */
Room::Room(string name , string owner , User  user)
{
	multiThreadLocker = new MultiThreadLocker(1);
	this->name = name;
	this->owner = owner;
	this->users.push_back(user);
}

/*
 * Returns users that are connected to the room
 */
vector<User> Room::getUserList()
{
	return users;
}

/*
 * Adds user to the room
 */
void Room::setUser(User User)
{
	multiThreadLocker->lock();
	this->users.push_back(User);
	multiThreadLocker->unlock();
}

/*
 * Erases user from the chat room
 */
bool Room::eraseUser(string user_name)
{
	for (vector <User>::iterator iter = users.begin(); iter != users.end(); iter++)
	{
		if(user_name.compare(iter->getName())==0)
		{
			multiThreadLocker->lock();
			users.erase(iter);
			multiThreadLocker->unlock();
			return true;
		}
	}
	return false;
}


/*
 * Returns owner of the room
 */
string Room::getOwner()
{
	return this->owner;
}

/*
 * Destructor - deletes room
 */
Room::~Room()
{
}

