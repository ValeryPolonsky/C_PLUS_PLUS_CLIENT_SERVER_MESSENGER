#include "UdpMessenger.h"

using namespace std;



UDPMessenger::UDPMessenger(int port)
{
	rcvClbk = NULL;
	flag=true;
	// create the socket
	socket = new UDPSocket (port);
	// start the thread to receive incoming messages
	this->start();
}

void UDPMessenger::run()
{
	// create a loop in which you read from the socket and print the received messages
	char buffer[1024];

	while (flag==true)
	{
		 bzero(buffer, 1024);
		 socket->recv(buffer,1024);
		 cout<<buffer<<endl;
	}
}

void UDPMessenger::sendTo(string msg,string ip , int port)
{
	socket->sendTo(msg , ip , port);
}


void UDPMessenger::reply(string msg)
{
	socket->reply(msg);
}

void UDPMessenger::close()
{
	// close the thread
     flag=false;
	// close the socket
     socket->cclose();
	// wait for thread to exit
    waitForThread();
	// delete and free any allocated resources
    delete socket;
}
