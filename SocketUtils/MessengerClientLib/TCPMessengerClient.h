#include <strings.h>
#include <map>
#include "string.h"
#include <vector>
#include "MThread.h"
#include "TCPSocket.h"
#include "TCPMessengerProtocol.h"
#include "MultipleTCPSocketsListener.h"
#include "UdpMessenger.h"
#include <sstream>
#include <string>
#include <stdlib.h>
#include "MultiThreadLocker.h"
using namespace std;


class TCPMessengerClient : MThread
{
	string userName;
	TCPSocket* client;
	bool runningSession;
	bool runningNormaly;
	UDPMessenger* udpMessenger;
	typedef map<string, string> NameToSocket;
	NameToSocket nameToSocket;
	MultiThreadLocker* multiThreadLocker;
	bool connected;
	bool loggedIn;
	string session;
	string withUser;
	string chatRoom;

public:

	/*
	 *Constructor - Initializes all clients's parameters
	 */
	TCPMessengerClient();

	/*
	 * Destructor - Deletes client
	 */
	~TCPMessengerClient();

	/*
	 * If the user is connected - do nothing
	 * If the user is not connected - creates a new TCPSocket with given ip and port
	 */
	bool connect(string ip);

	/*
	 * If the client is connected - return true, else false
	 */
	bool isConnected();

	/*
	 * Disconnects from the server
	 * If the client is connected and logged in - disconnection occurs
	 */
	bool disconnect();

	/*
	 * If the user is logged in - creates session between this users and user that got by name
	 */
	bool open(string userName);

	/*
	 * If the client has active session - returns true, else false
	 */
	bool isActiveClientSession();

	/*
	 * If the user logged in - sends message through udp messenger
	 */
	bool send(string msg);

	/*
	 * If the user is connected and not logged in - sends command and data to the server with registration request
	 */
	bool signup(string userToSignUp , string pass);

	/*
	 * If the user is connected to the server and not logged in - sends data and command to the server with log in request
	 */
	bool login(string userToLogin , string pass);

	/*
	* If the client is logged in - close active session with partner
	*/
	bool closeActiveSessionWithPeer();

	/*
	 * Prints user's list from server
	 */
	bool printListOfUsers();

	/*
	 * Returns user name
	 */
	string getUsername();

	/*
	 * Reads length of the message
	 */
	int readLength(TCPSocket* sock);

	/*
	 * Requests to display connected users
	 */
	bool printConnectedUsers();

	/*
	 * Updates users list
	 */
	void updateUserList(map<string,string>m);

	/*
	 * Opens session with chat room
	 */
	void openSessionWithChatRoom(string chatRoom);

	/*
	 * Adds users to map
	 */
    void addUsersToUsersMap(TCPSocket * sock ,int length);

    /*
     * Extracts port from string
     */
	string splitFirst(string all);

	/*
	 * Extracts address from string
	 */
	string splitSecond(string all);

	/*
	 * Searches user name in user's map
	 */
	string searchByName(string name);

	/*
	 * Requests users in room from server
	 */
	void getUserFromRoom(string room);

	/*
	 * Creates a new chat room
	 */
	void createChatroom(string room_name);

	/*
	 * Checks if strings are equal
	 */
	bool checkErrorStatus(string str , string error);

	/*
	 * Exits from room
	 */
	bool exitFromRoom();

	/*
	 * Receives status from server
	 */
	void getStatus(string userName);

	/*
	 * Prints status of some user
	 */
	void printStatus(TCPSocket * sock);

	/*
	 * Closes specific room
	 */
    void closeRoom(string room_name);

    /*
     * Deletes all users in session
     */
    void deleteAllusersInSession();

    /*
     * Prints status of current client
     */
	void getMystatus();

	/*
	 * Requests rooms list
	 */
	void printRooms();

	/*
	 * Runs client thread with commands switch cases
	 */
	void run();

	/*
	 * Prints users map
	 */
	void printMap();
	//case methods

	/*
	 * Deletes user from session
	 */
	void closeSessionWithPeerReply();

	/*
	 * Deletes all users in session
	 */
	void eraseMsgReply();

	/*
	 * Deletes all connected users in the room
	 */
	void closeRoomReply();

	/*
	 * Deletes all users in the room and prints status
	 */
	void exitFromRoomReply(TCPSocket *cSocket);

	/*
	 * Displays session connection Reply
	 */
	void joinSessionWithCrReply(TCPSocket *cSocket);

	/*
	 * Displays chat room list from server
	 */
	void displayChatRoomsReply(TCPSocket *cSocket);

	/*
	 * Creates a new chat room
	 */
	void openChatRoomReply(TCPSocket *cSocket);

	/*
	 * Creates session with peer
	 */
	void createSessionWithPeerReply(TCPSocket *cSocket);

	/*
	 * Reads connected users list from socket
	 */
	void displayConnUsersReply(TCPSocket *cSocket);

	/*
	 * Reads users list from server
	 */
	void displayUsersListReply(TCPSocket *cSocket);

	/*
	 * Reads registration Reply from server
	 */
	void signUpReply(TCPSocket *cSocket);

	/*
	 * Reads log in Reply from server
	 */
	void logInReply(TCPSocket *cSocket);
};

