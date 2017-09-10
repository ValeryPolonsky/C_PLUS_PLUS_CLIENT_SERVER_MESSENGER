#ifndef LoginAndRegister_H_
#define LoginAndRegister_H_

#include <strings.h>
#include <string.h>
#include <map>
#include <vector>
#include "MThread.h"
#include "TCPSocket.h"
#include <iostream>
#include <fstream>
#include "TCPMessengerProtocol.h"
#include "Dispatcher.h"
#include "MultiThreadLocker.h"

using namespace std;

class LoginAndRegister : MThread
{
	typedef map <string, TCPSocket*> SocketsMap;
	SocketsMap openedpeers;
	bool runningNormally;
	Dispatcher* dispatcher;
	MultiThreadLocker* multiThreadLocker;
	map <string, string> loggedIn;

public:

	/*
	 * Initializes all data members of the class
	 */
	LoginAndRegister();

	/*
	 * Checks if the user is registered
	 */
	bool isSignedUp(string userName);

	/*
	 * Adds peer to the peers map
	 */
	void addPeer(TCPSocket* p);

	/*
	 * Registrates a new user
	 */
	string signUp(string userName, string pass);

	/*
	 * Starts log in and register thread
	 */
	void run();

	/*
	 * Logs in user with given name and password
	 */
	string login(string name, string pass ,  TCPSocket * p);

	/*
	 * Returns length of users list
	 */
	static  int linesLength();

	/*
	 * Sends all registered users from the file
	 */
	static void sendUsersFromFile(TCPSocket * p);
	//char* getFirstWordInString(char* strFullString, char* strFirstWord);

	/*
	 * Prints all registered users
	 */
	void printAllUsers();

	/*
	 * Returns dispatcher pointer
	 */
	Dispatcher* getDispatcher();

	/*
	 * Checks if the user is logged in
	 */
	bool isloggedInBefore(string user_name);

	/*
	 * Log in execution
	 */
	void LogInExecute(TCPSocket * readypeer , int Command);

	/*
	 * Registration execution
	 */
	void signUpExecute(TCPSocket * readypeer , int Command);

	/*
	 * Error condition
	 */
	void error(TCPSocket * readypeer , int Command);

	/*
	 * Checks if the given address is in logged in map
	 */
	bool isLogin(string Address , map<string , TCPSocket *> mapi);

	/*
	 * Detructor - deletes log in and register data
	 */
	virtual ~LoginAndRegister();
};


#endif /* LoginAndRegister_H_ */
