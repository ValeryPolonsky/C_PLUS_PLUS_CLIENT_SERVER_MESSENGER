#ifndef UDPMESSENGER_H_
#define UDPMESSENGER_H_

#include <pthread.h>
#include "UDPSocket.h"
#include "MThread.h"
using namespace std;


class OnRecieveClbk {
public:
	virtual void handleMessage(string msg)=0;
	virtual ~OnRecieveClbk(){}
};

class UDPMessenger: public MThread{
	UDPSocket* socket;
	bool flag;
private:
	OnRecieveClbk* rcvClbk;

public:

	UDPMessenger(int port);


	/**
	 * sends the given message to the given peer specified by IP
	 */
	void sendTo(string msg,string ip , int port);

	/**
	 * reply to an incoming message, this method will send the given message
	 * the peer from which the last message was received.
	 */
	void reply(string msg);

	/**
	 * close the messenger and all related objects (socket)
	 */
	void close();

	/**
	 * This method runs in a separate thread, it reads the incoming messages
	 * from the socket and prints the content on the terminal.
	 * The thread should exist when the socket is closed
	 */
	void run();

};

#endif
