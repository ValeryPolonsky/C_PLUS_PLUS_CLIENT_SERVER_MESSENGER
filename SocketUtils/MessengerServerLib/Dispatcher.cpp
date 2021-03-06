#include "Dispatcher.h"
#include "TCPMessengerServer.h"
#include "UDPSocket.h"
#include "User.h"

/*
 * Constructor - creates a new dispatcher with given users map
 */
Dispatcher::Dispatcher(map<string, TCPSocket*>* mapi , map<string , string > *loggedIn)
{
	multiThreadLocker = new MultiThreadLocker(1);
	this->connected= mapi;
	this->loggedIn= loggedIn;
	running= true;
	this->start();

}

/*
 * Starts dispatcher thread
 */
void Dispatcher::run ()
{
	running = true;

	while (running)
	{
		TCPSocket * readypeer = TCPMessengerServer::MapToReady(&users);
		int Command = TCPMessengerProtocol::readCommand(readypeer);
		switch (Command)
		{
		case PRINT_USER_LIST:
		{
			printUserList(readypeer , Command);
			break;
		}
		case PRINT_USER_CONNECTED:
		{
			userConnected(readypeer , Command);
			break;
		}
		case OPEN_SESSION_WITH_PEER:
		{
			createSessionWithPeer(readypeer , Command);
			break;
		}
		case CREATE_CHAT_ROOM:
		{
			openRoom(readypeer , Command);
			break;
		}
		case PRINT_CHAT_ROOM:
		{
			displayAllRooms(readypeer , Command);
			break;
		}
		case OPEN_SESSION_WITH_CHAT_ROOM:
		{
			joinRoom(readypeer , Command);
			break;
		}
		case PRINT_USER_IN_ROOM:
		{
			printRoomsUsers(readypeer , Command);
			break;
		}
		case GET_STATUS:
		{
			getStatus(readypeer , Command);
			break;
		}
		case EXIT_FROM_ROOM:
		{
			exitFromRoom(readypeer , Command);
			break;
		}
		case CLOSE_ROOM:
		{
			closeRoom(readypeer);
			break;
		}
		case CLOSE_SESSION_WITH_PEER:
		{
			closeSessionWithPeer(readypeer);
			break;
		}
		case DISCONECT:
		{
			disconnectFromServer(readypeer , Command);
		}

		}
	}
	cout << "Dispatcher listener has ended." << endl;
}

/*
 * Prints status that user is connected
 */
void Dispatcher::userConnected(TCPSocket* readypeer , int Command)
{
	int length = this->objectlength();
	TCPMessengerProtocol::sendCommand(readypeer , Command);
	TCPMessengerServer::sendLength(readypeer , length);
	this->sendUsersFromMap(readypeer);
}

/*
 * Finds user in users map and creates session with him if he's not busy or not connected
 */
void Dispatcher::createSessionWithPeer(TCPSocket * readypeer , int Command)
{
	string user2 = TCPMessengerProtocol::readData(readypeer);
	if(UserSearch(user2)==NULL)
	{
		TCPMessengerProtocol::sendCommand(readypeer , USER_NOT_FOUND);
		return;
	}
	if(UserSearch(user2)->getStatus().compare("IN")==0)
	{
		TCPMessengerProtocol::sendCommand(readypeer , USER_BUSY);
		return;
	}
	this->sendErrorstatus(readypeer, this->UserSearch(user2), Command);
	string user1 = this->searchByUser(readypeer);
	User u = *this->UserSearch(user2);
	TCPMessengerProtocol::sendCommand(&u , Command);
	TCPMessengerProtocol::sendData(&u ,readypeer->destIpAndPort());
	TCPMessengerProtocol::sendData(&u ,user1);
	TCPMessengerProtocol::sendCommand(readypeer , Command);
	TCPMessengerProtocol::sendData(readypeer,u.destIpAndPort());
	TCPMessengerProtocol::sendData(readypeer , user2);
	multiThreadLocker->lock();
	sessions.insert(pair<string , string>(user1 , user2));
	multiThreadLocker->unlock();
	this->UserSearch(user1)->setSessionStatus();
	this->UserSearch(user2)->setSessionStatus();
}

/*
 * Opens a new chat room
 */
void Dispatcher::openRoom(TCPSocket * readypeer , int Command)
{
	string room_name = TCPMessengerProtocol::readData(readypeer);
	if (isExistRoom(room_name)==true)
	{
		TCPMessengerProtocol::sendCommand(readypeer , ROOM_IS_EXIST);
		return;
	}
	TCPMessengerProtocol::sendCommand(readypeer , Command);
	string user_name = this->SearchByIp(readypeer->destIpAndPort());
	Room cr(room_name,user_name,*this->UserSearch(user_name));

	multiThreadLocker->lock();
	rooms.insert(pair<string ,Room>(room_name , cr));
	multiThreadLocker->unlock();

	TCPMessengerProtocol::sendData(readypeer , "Chat room was created\n");
	TCPMessengerProtocol::sendData(readypeer , room_name);
	this->UserSearch(user_name)->setSessionStatus();
	this->UserSearch(user_name)->setRoom(room_name);
}

/*
 * Prints users list
 */
void Dispatcher::printUserList(TCPSocket* readypeer, int Command)
{
	int length = LoginAndRegister::linesLength();
	TCPMessengerProtocol::sendCommand(readypeer, Command);
	TCPMessengerServer::sendLength(readypeer, length);
	LoginAndRegister::sendUsersFromFile(readypeer);
}

/*
 * Displays all cretaed chat rooms
 */
void Dispatcher::displayAllRooms(TCPSocket * readypeer,int Command)
{
	int length = this->rooms_length();
	TCPMessengerProtocol::sendCommand(readypeer , Command);
	TCPMessengerServer::sendLength(readypeer , length);
	this->sendRoomsName(readypeer);
}

/*
 * Joins the user to the chat room
 */
void Dispatcher::joinRoom(TCPSocket * readypeer,int Command)
{
	string roomName = TCPMessengerProtocol::readData(readypeer);
	string user_name =  this->searchByUser(readypeer);
	User  user(user_name  , readypeer);
	Room * cr;
	if(this->FindByNameRoom(roomName)==NULL){
		cout<<"error2"<<endl;
		TCPMessengerProtocol::sendCommand(readypeer , SESSION_REFUSED);
		return;
	}else
		cr = FindByNameRoom(roomName);
	cr->setUser(user);
	this->updateUsersAfterConnection( cr->getUserList() , Command , roomName);
	this->UserSearch(user_name)->setSessionStatus();
}

/*
 * Disconnects users from server
 */
void Dispatcher::disconnectFromServer(TCPSocket * readypeer , int Command)
{
	string user_name = TCPMessengerProtocol::readData(readypeer);
	multiThreadLocker->lock();
	this->users.erase(user_name);
	multiThreadLocker->unlock();
	for (map <string, string>::iterator iter = loggedIn->begin(); iter != loggedIn->end(); iter++)
    {
		if(user_name.compare(iter->first)==0)
		{
			multiThreadLocker->lock();
			this->loggedIn->erase(iter->first);
			multiThreadLocker->unlock();
		}
    }

	for (map <string , Room  >:: iterator iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		if(iter->second.getOwner().compare(user_name)==0)
		{
			this->eraseSessionStatusfromAllUsersInRoom(this->FindByNameRoom(iter->first)->getUserList());
			multiThreadLocker->lock();
			this->rooms.erase(iter->first);
			multiThreadLocker->unlock();
		}
	}
	multiThreadLocker->lock();
	this->connected->erase(readypeer->destIpAndPort());
	multiThreadLocker->unlock();

	cout<<"disconnected: "<<readypeer->destIpAndPort()<<endl;

}

/*
 * Displays all users in chat room
 */
void Dispatcher::printRoomsUsers(TCPSocket * readypeer , int Command)
{

	string roomName = TCPMessengerProtocol::readData(readypeer);
	if(this->isExistRoom(roomName)==false){TCPMessengerProtocol::sendCommand(readypeer , ROOM_NOT_FOUND); return;}
	TCPMessengerProtocol::sendCommand(readypeer , Command);
	TCPMessengerServer::sendLength(readypeer , this->FindByNameRoom(roomName)->getUserList().size());
	this->sendUsersFromRoom(readypeer , this->FindByNameRoom(roomName)->getUserList());
}

/*
 * Returns status of the user
 */
void Dispatcher::getStatus(TCPSocket* readypeer, int Command)
{
	string userName = TCPMessengerProtocol::readData(readypeer);
	if(UserSearch(userName) == NULL)
	{
		TCPMessengerProtocol::sendCommand(readypeer, USER_NOT_FOUND);
		return;
	}
	TCPMessengerProtocol::sendCommand(readypeer, Command);
	TCPMessengerProtocol::sendData(readypeer, this->UserSearch(userName)->getStatus());
	TCPMessengerProtocol::sendData(readypeer, this->UserSearch(userName)->getRoom());
}

/*
 * Disconnects the user from the specific room
 */
void Dispatcher::exitFromRoom(TCPSocket * readypeer , int Command)
{
	string roomName =  TCPMessengerProtocol::readData(readypeer);
	string user_Name = this->searchByUser(readypeer);
	if(this->eraseFromRoom(user_Name , this->FindByNameRoom(roomName))==true)
	{
		int sizeBeforeUpdate=this->FindByNameRoom(roomName)->getUserList().size()-1;
		if(this->FindByNameRoom(roomName)->getUserList().size()<0)
		{
			TCPMessengerProtocol::sendCommand(readypeer, Command);
			TCPMessengerServer::sendLength(readypeer, sizeBeforeUpdate);
			TCPMessengerProtocol::sendData(readypeer, "NONE");
		}
		else
		{
			this->updateUsersAfterConnection(this->FindByNameRoom(roomName)->getUserList(), Command, roomName);
		}
	}
	else
	{
		TCPMessengerProtocol::sendCommand(readypeer, EXIT_FROM_ROOM_NOT_SUCCESS);
	}
}

/*
 * Closes session with peer
 */
void Dispatcher::closeSessionWithPeer(TCPSocket* readypeer)
{
	string user_name1 = TCPMessengerProtocol::readData(readypeer);
	this->UserSearch(user_name1)->eraseSessionStatus();
	this->UserSearch(user_name1)->setRoom("NONE");

	string user_name2 = this->searchByUser(readypeer);
	this->UserSearch(user_name2)->eraseSessionStatus();
	this->UserSearch(user_name2)->setRoom("NONE");

	multiThreadLocker->lock();
	sessions.erase((user_name1));
	sessions.erase((user_name2));
	multiThreadLocker->unlock();

	TCPMessengerProtocol::sendCommand(readypeer, CLOSE_SESSION_WITH_PEER);
	TCPMessengerProtocol::sendCommand(this->UserSearch(user_name1) , CLOSE_SESSION_WITH_PEER);

}

/*
 * Closes a specific room
 */
void Dispatcher::closeRoom(TCPSocket * readypeer)
{
	string roomName = TCPMessengerProtocol::readData(readypeer);
	string owner = this->FindByNameRoom(roomName)->getOwner();
	string userName = this->searchByUser(readypeer);
	if(this->checkWhoIsOwner(owner , userName)==true)
	{
		this->eraseSessionStatusfromAllUsersInRoom(this->FindByNameRoom(roomName)->getUserList());
		multiThreadLocker->lock();
		rooms.erase(roomName);
		multiThreadLocker->unlock();
	}
	else
	{
		TCPMessengerProtocol::sendCommand(readypeer , ERROR_OWNER);
	}
}


/*
 * Displays connected users
 */
void Dispatcher::printConnectedUsers()
{
	cout << "The users are:" << endl;
 	for (map<string, User>::iterator iter = users.begin(); iter != users.end(); iter++)
	{
		cout << iter->first << endl;
	}
}


/*
 * Displays all created rooms
 */
void Dispatcher::printAllRooms()
{
	cout << "The rooms are:" << endl;
	for (map <string , Room  >:: iterator iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		cout << iter->first << endl;
	}
}

/*
 * Prints all users that are connected to the room
 */
void Dispatcher::printAllUserInRoom(string room_name)
{
	cout << "The users are" << endl;
	for (map <string, Room  >:: iterator iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		if(iter->first.compare(room_name) == 0)
		{
			this->printVector(iter->second.getUserList());
		}
	}
}

/*
 * Prints vector of users
 */
void Dispatcher::printVector(vector<User> vec)
{
	for (vector<User>::iterator iter = vec.begin(); iter != vec.end(); iter++)
	{
		cout<<iter->getName();
	}
}


/*
 * Prints all opened sessions
 */
void Dispatcher::printAllSessions()
{
	cout << "The session are" << endl;
	for (map <string , string   >:: iterator iter = sessions.begin(); iter != sessions.end(); iter++)
	{
		cout << iter->first << " in session with " << iter->second << endl;
	}
}

/*
 * Deletes room session in all users in the room
 */
void Dispatcher::eraseSessionStatusfromAllUsersInRoom(vector<User > vec)
{
	for (vector<User>::iterator iter = vec.begin(); iter != vec.end(); iter++)
	{
		TCPMessengerProtocol::sendCommand(this->UserSearch(iter->getName()), CLOSE_ROOM);
		UserSearch(iter->getName())->eraseSessionStatus();
		UserSearch(iter->getName())->setRoom("NONE");
	}
}

/*
 * Checks if the user exists in the room
 */
bool Dispatcher::isExistRoom(string room_name)
{
	for(map <string, Room >:: iterator iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		if(iter->first.compare(room_name) == 0)
		{
			return true;
		}
	}
	return false;
}

/*
 * Checks if the given user is the owner
 */
bool Dispatcher::checkWhoIsOwner(string owner , string user)
{
	if(owner.compare(user)==0)
	{
		return true;
	}
	return false;
}

/*
 * Deletes user from the room
 */
bool Dispatcher::eraseFromRoom(string user , Room * cr)
{
	if(cr->eraseUser(user)==true)
	{
		TCPMessengerProtocol::sendCommand(this->UserSearch(user) , ERASE_MSG);
		this->UserSearch(user)->setRoom("NONE");
		this->UserSearch(user)->eraseSessionStatus();
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * Sends error status
 */
bool Dispatcher::sendErrorstatus(TCPSocket* sock, User* user, int Command)
{
	if(user->getStatus().compare("IN") == 0)
	{
		TCPMessengerProtocol::sendCommand( sock , Command);
		TCPMessengerProtocol::sendData(sock,"IN");
		return true;
	}
	return false;
}

/*
 * Sends users that are connected to room
 */
void Dispatcher::sendUsersFromRoom(TCPSocket * sock , vector<User > vec )
{
	for (vector <User >:: iterator iter = vec.begin(); iter != vec.end(); iter++)
	{
		TCPMessengerProtocol::sendData(sock , iter->getName());
	}
}


/*
 * Returns number of users that are connected to the room
 */
int  Dispatcher::rooms_length()
{
	int length=0;

	for(map <string, Room >:: iterator iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		length++;
	}
	return length;
}

/*
 * Returns number of users in the given vector
 */
int Dispatcher::getNumberOfUsers(vector<User>  vec)
{
	int NumofUsers = -1;
	for (vector <User >:: iterator iter = vec.begin(); iter != vec.end(); iter++)
	{
		NumofUsers++;
	}
	return NumofUsers;
}

/*
 * Searches room by it's name in the rooms map
 */
Room* Dispatcher::FindByNameRoom(string roomName)
{
	for(map <string, Room >:: iterator iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		if(roomName.compare(iter->first)==0)
		{
			return &iter->second;
		}
	}
	return NULL;
}

/*
 * Sends room name through given socket
 */
void Dispatcher::sendRoomsName(TCPSocket * p)
{
	for(map <string, Room>::iterator iter = rooms.begin(); iter != rooms.end(); iter++)
	{
		TCPMessengerProtocol::sendData(p,iter->first);
	}
}


/*
 * Adds user to the users map
 */
void Dispatcher::addUser(string name, TCPSocket* p)
{
	User user(name, p);
	multiThreadLocker->lock();
	this->users.insert(pair< string , User > (name , user));
	multiThreadLocker->unlock();
}


/*
 * Returns length of users map
 */
int Dispatcher::objectlength()
{
	int length=0;

	for(map <string, User>::iterator iter = users.begin(); iter != users.end(); iter++)
	{
		length++;
	}
	return length;
}

/*
 * Sends users from the map
 */
void Dispatcher::sendUsersFromMap(TCPSocket * p)
{
	for(map <string, User >:: iterator iter = users.begin(); iter != users.end(); iter++)
	{
		TCPMessengerProtocol::sendData(p, iter->first);
	}
}

/*
 * Updates users details after connection
 */
bool Dispatcher::updateUsersAfterConnection(vector<User> vec, int Command, string Data)
{
	for (vector<User>::iterator iter = vec.begin(); iter != vec.end(); iter++)
	{
		string userName= iter->getName();

		TCPMessengerProtocol::sendCommand(this->UserSearch(userName),Command);
		int length = vec.size()-1;
		TCPMessengerServer::sendLength(this->UserSearch(userName) , length );

		for (vector <User >:: iterator iter2 = vec.begin(); iter2 != vec.end(); iter2++)
		{
			if(userName.compare(iter2->getName())!=0)
			{
				string user = iter2->getName()+":"+iter2->destIpAndPort();
				TCPMessengerProtocol::sendData(this->UserSearch(userName), user);
			}
		}
		TCPMessengerProtocol::sendData(this->UserSearch(userName),Data);
	}
	return true;
}


/*
 * Searches user in users map by his name
 */
User* Dispatcher::UserSearch(string Name)
{
	for(map <string, User >:: iterator iter = users.begin(); iter != users.end(); iter++)
	{
		if (Name.compare(iter->first)==0)
		{
			return &iter->second;
		}
	}
	return NULL;
}

/*
 * Searches user by socket in users map
 */
string Dispatcher::searchByUser(TCPSocket* user)
{
	for(map <string, User >:: iterator iter = users.begin(); iter != users.end(); iter++)
	{
		if (user == &iter->second)
		{
			return iter->first;
		}
	}

	return NULL;
}

/*
 * Searches user by his IP address
 */
string Dispatcher::SearchByIp(string Ip)
{

	for(map <string, User >:: iterator iter = users.begin(); iter != users.end(); iter++)
	{
		if (Ip.compare(iter->second.destIpAndPort())==0)
		{
			return iter->first;
		}
	}
	return NULL;
}

/*
 * Destructor
 */
Dispatcher::~Dispatcher() {
}
