#ifndef MESSENGERSERVER_H_
#define MESSENGERSERVER_H_


#include <strings.h>
#include <string.h>
#include <map>
#include <vector>
#include "MThread.h"
#include "TCPSocket.h"
#include "MultipleTCPSocketsListener.h"
#include "TCPMessengerProtocol.h"
#include "LoginAndRegister.h"
#include "MultiThreadLocker.h"


using namespace std;




class TCPMessengerServer : MThread
{
	friend class User;
	TCPSocket * serverSocket;
	bool runningNormally;
	LoginAndRegister* login;
	MultiThreadLocker* multiThreadLocker;

public:

	TCPMessengerServer();

	void run();

    /*
     * Returns login
     */
    LoginAndRegister * getLogin();

    /*
     * Sends length of the message through socket
     */
    static void sendLength(TCPSocket* sock, int Length);

    /*
     * Converts between map and vector
     */
    //vector<TCPSocket*>  MapToVector(map<string,TCPSocket *> *mapi);

    /*
     * Returns ready peer
     */
    static TCPSocket* MapToReady(map<string , User >* mapi);

    /*
     * Returns ready socket
     */
    static TCPSocket* MapToReadyConnected(map<string ,TCPSocket *>* mapi);

    /*
     * Closes server
     */
	void close();
};

#endif
