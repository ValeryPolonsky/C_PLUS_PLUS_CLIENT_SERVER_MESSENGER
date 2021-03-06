/*
 * TestMessengerClient.cpp
 *
 *  Created on: May 25, 2016
 *      Author: user
 */

#include "TestMessengerClient.h"

#include <iostream>
#include <string.h>
#include "TCPMessengerClient.h"

using namespace std;

TestMessengerClient::TestMessengerClient() {
}

TestMessengerClient::~TestMessengerClient() {
	// TODO Auto-generated destructor stub
}

bool TestMessengerClient::test()
{


	    TCPMessengerClient * client1 = new TCPMessengerClient();
	    TCPMessengerClient * client2 = new TCPMessengerClient();
		string message = "";
		string username1 = "valery";
		string username2 = "tomer";
		string name = "";
		string chatRoomName = "myroom";
		string ip = "127.0.0.1";
		string password1 = "1234";
		cout<<"****Connection of user1:**** "<<endl;
		client1->connect(ip); // c command
		sleep(2);
		cout<<endl<<"****Log in of the user1:**** "<<endl;
		client1->login(username1 , password1); // login command
		sleep(2);
		cout<<endl<<"****List of registered users:**** "<<endl;
		client1->printListOfUsers(); // lu command
		sleep(2);
		cout<<"****List of the connected users:**** "<<endl;
		client1->printConnectedUsers();  // lcu command
		sleep(2);
		cout<<endl<<"****User's status:**** "<<endl;
		client1->getMystatus(); // l command
		sleep(2);
		cout<<endl<<"****Create a new chat room:**** "<<endl;
		client1->createChatroom(chatRoomName); // cnr command
		sleep(2);
		cout<<endl<<"****Connection of user2:**** "<<endl;
		client2->connect(ip); // c command
		sleep(2);
		cout<<endl<<"****Log in of the user2:**** "<<endl;
		client2->login(username2 , password1); // login command
		sleep(2);
		cout<<endl<<"****user2 joining the room user1 opened:**** "<<endl;
		client2->openSessionWithChatRoom("myroom");
		sleep(2);
		cout<<endl<<"****user2 sending a message:**** "<<endl;
		client2->send("hello user1!");
		sleep(2);
		cout<<endl<<"****user1 sending a message back:**** "<<endl;
		client1->send("Hi user2!");
		sleep(1);
		cout<<endl<<"****List of existing rooms:**** "<<endl;
		client1->printRooms();
		sleep(2);
		cout<<endl<<"****Users that are in the room:**** "<<endl;
		client1->getUserFromRoom(chatRoomName); // lru command
		sleep(2);
		cout<<endl<<"****User2 leaving the room**** "<<endl;
		client2->exitFromRoom(); // csr command
		sleep(2);
		cout<<endl<<"****User1 leaving the room**** "<<endl;
		client1->exitFromRoom(); // csr command
		sleep(1);
		cout<<endl<<"****Users that are in the room:**** "<<endl;
		client1->getUserFromRoom(chatRoomName); // lru command
		sleep(2);
		client1->closeRoom(chatRoomName); // cr command
		sleep(2);

		cout<<endl<<endl<<"****Testing sending mechanism:****"<<endl;
		cout<<endl<<"Client 1 opened session with client2."<<endl;
		client1->open("tomer");
		sleep(1);
		client1->send("Hi Tomer!");
		sleep(1);
		client2->send("Hi Valery!");
		sleep(2);
		cout<<"Closing session"<<endl;
		client1->closeActiveSessionWithPeer();
		sleep(1);

		client1->disconnect(); // d command
		sleep(2);
		client2->disconnect(); // d command
		sleep(2);
		//messenger->disconnect();
		delete client1;
		delete client2;
		cout<<endl<<"Messenger has been closed"<<endl;
		return true;
}




