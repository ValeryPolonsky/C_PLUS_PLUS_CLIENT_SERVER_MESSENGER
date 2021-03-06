#include "TCPMessengerServer.h"
#include "Dispatcher.h"


using namespace std;

/*
 * Initializes all data members of the class
 */
LoginAndRegister::LoginAndRegister(){

	multiThreadLocker = new MultiThreadLocker(1);
	runningNormally = true;
	dispatcher = new Dispatcher(&openedpeers, &loggedIn);
	this->start();
}

/*
 * Starts log in and register thread
 */
void LoginAndRegister::run()
{
	runningNormally = true;
	while (runningNormally)
	{
		TCPSocket * readypeer = TCPMessengerServer::MapToReadyConnected(&openedpeers);
		int Command = TCPMessengerProtocol::readCommand(readypeer);
		switch (Command)
		{
		case LOG_IN:
		{
			LogInExecute(readypeer , Command);
			break;
		}
		case SIGN_UP:{

			signUpExecute(readypeer , Command);
			break;
		}
		case LOGIN_ERASE:
		{
			error(readypeer , Command);
			break;
		}
		}
	}
}

/*
 * Error condition
 */
void LoginAndRegister::error(TCPSocket * readypeer , int Command)
{
	multiThreadLocker->lock();
	openedpeers.erase(readypeer->destIpAndPort());
	multiThreadLocker->unlock();
	cout<<"disconnected: "<<readypeer->destIpAndPort()<<endl;
}

/*
 * Registration execution
 */
void LoginAndRegister::signUpExecute(TCPSocket * readypeer , int Command)
{
	string name = TCPMessengerProtocol::readData(readypeer);
	string pass = TCPMessengerProtocol::readData(readypeer);
	string str = signUp(name , pass);
	TCPMessengerProtocol::sendCommand(readypeer, Command);
	TCPMessengerProtocol::sendData(readypeer, str);
}

/*
 * Log in execution
 */
void LoginAndRegister::LogInExecute(TCPSocket * readypeer , int Command)
{
	string name = TCPMessengerProtocol::readData(readypeer);
	string pass = TCPMessengerProtocol::readData(readypeer);
	if(isloggedInBefore(name)==true) { TCPMessengerProtocol::sendCommand(readypeer , USER_IS_EXIST); return ;}
	string str = login(name, pass , readypeer);
	if(str.compare("false")==0) { TCPMessengerProtocol::sendCommand(readypeer ,LOGIN_NOT_SUCCESS); return;}
	TCPMessengerProtocol::sendCommand(readypeer, Command);
	TCPMessengerProtocol::sendData(readypeer, str);
	TCPMessengerProtocol::sendData(readypeer , readypeer->destIpAndPort());
}


/*
 * Checks if the user is registered
 */
bool LoginAndRegister::isSignedUp(string userName)
{
	string line;
	ifstream myReadFile("users_and_passwords.txt");
	if (myReadFile.is_open())
	{
		while (myReadFile.good())
		{
			getline(myReadFile, line);
			if (line.compare(userName)==0)
			{
				return true;
			}
		}
	}
	myReadFile.close();
	return false;
}

/*
 * Returns dispatcher pointer
 */
Dispatcher * LoginAndRegister::getDispatcher()
{
	return dispatcher;
}

/*
 * Sends all registered users from the file
 */
void LoginAndRegister::sendUsersFromFile(TCPSocket * p)
{
	string line;
	ifstream myReadFile("users_and_passwords.txt");
	if (myReadFile.is_open())
	{
		while (myReadFile.good())
		{
			getline(myReadFile, line);
			string delimiter = " ";
			string username = line.substr(0,line.find(delimiter));
			string password = line.substr(line.find(delimiter)+1,line.length());
			TCPMessengerProtocol::sendData(p , username);
		}
	}
	myReadFile.close();
}

/*
 * Prints all registered users
 */
void LoginAndRegister::printAllUsers()
{
	string line;
	ifstream myReadFile("users_and_passwords.txt");
	if (myReadFile.is_open())
	{
		cout<<"The users Are:"<<endl;
		while (myReadFile.good())
		{
			getline(myReadFile, line);
			string delimiter = " ";
			string username = line.substr(0,line.find(delimiter));
			string password = line.substr(line.find(delimiter)+1,line.length());
			cout<<username<<endl;
		}
	}
	myReadFile.close();

}

/*
 * Registrates a new user
 */
string LoginAndRegister::signUp(string userName , string pass)
{
	if (this->isSignedUp(userName +" "+pass) == false)
	{
		ofstream myfile;
		myfile.open ("users_and_passwords.txt", std::ios_base::app);
		myfile << userName << " "<<pass<<endl;
		myfile.close();
		return "Signed Up";
	}
	else
	{
		return "!!!User with this name already exists!!!";
	}
}

/*
 * Logs in user with given name and password
 */
string LoginAndRegister::login(string name, string pass , TCPSocket * p)
{
	if ((this->isSignedUp(name+" "+pass)==false))
	{
		return "false";
	}

	multiThreadLocker->lock();
	openedpeers.erase(p->destIpAndPort());
	multiThreadLocker->unlock();

	multiThreadLocker->lock();
	loggedIn.insert(pair<string, string>(name, p->destIpAndPort()));
	multiThreadLocker->unlock();

	dispatcher->addUser(name, p);

	return "You have logged in successfully";
}

/*
 * Adds peer to the peers map
 */
void LoginAndRegister::addPeer ( TCPSocket * p)
{
	openedpeers.insert(pair<string, TCPSocket*>(p->destIpAndPort(), p));
}

/*
 * Returns length of users list
 */
int LoginAndRegister::linesLength()
{
	int numLines = 0;
	ifstream in("users_and_passwords.txt");
	string unused;
	while (getline(in, unused))
	{
		numLines++;
	}

	in.close();
	return numLines;
}

/*
 * Checks if the given address is in logged in map
 */
bool LoginAndRegister::isLogin(string Address, map<string, TCPSocket*> mapi)
{
	for(map<string, TCPSocket*>::iterator it = mapi.begin(); it != mapi.end(); it++)
	{
		if(it->first.compare(Address) == 0)
		{
			return true;
		}
	}
	return false;
}

/*
 * Checks if the user is logged in
 */
bool LoginAndRegister::isloggedInBefore(string user_name)
{
	for(map<string, string>::iterator it = loggedIn.begin(); it != loggedIn.end(); it++)
	{
		if(user_name.compare(it->first)==0)
		{
			return true;
		}
	}
	return false;
}

/*
 * Detructor - deletes log in and register data
 */
LoginAndRegister::~LoginAndRegister()
{
}
