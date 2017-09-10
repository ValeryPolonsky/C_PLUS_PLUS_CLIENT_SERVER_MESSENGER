#include "TestMessengerClient.h"
#include "TCPMessengerServer.h"
#include "TCPMessengerClient.h"
#include <strings.h>
#include <string.h>
#include <map>
#include <vector>
#include "MThread.h"
#include "TCPSocket.h"
#include<iostream>
#include<fstream>
#include "TCPMessengerProtocol.h"
#include "UDPSocket.h"
#include "User.h"
#include "Room.h"
#include "MultiThreadLocker.h"

using namespace std;
int main(){
	TCPMessengerServer* msngrServer = new TCPMessengerServer();
	sleep(2);

	TestMessengerClient* client1=new TestMessengerClient();
	if(!client1->test())
		cout << "Test failed!!" << endl;
	else
		cout<<"Test succeded!!"<<endl;
	return 0;
}




