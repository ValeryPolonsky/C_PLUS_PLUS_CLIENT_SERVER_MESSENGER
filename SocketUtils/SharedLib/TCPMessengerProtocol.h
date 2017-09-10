#ifndef TCPMESSENGERPROTOCOL_H_
#define TCPMESSENGERPROTOCOL_H_

#include "strings.h"
#include "string.h"
#include <string>
#define MSNGR_PORT 3346

#define LOGIN_ERASE                 0
#define CLOSE_SESSION_WITH_PEER 	1
#define OPEN_SESSION_WITH_PEER 		2
#define EXIT						3
#define SEND_MSG_TO_PEER			4
#define SESSION_REFUSED				5
#define SESSION_ESTABLISHED			6
#define LOG_IN						7
#define SIGN_UP                     8
#define REJECT                      9
#define NOT_A				        10
#define PRINT_USER_LIST             11
#define PRINT_USER_CONNECTED        12
#define CREATE_CHAT_ROOM			13
#define CLOSE_CHAT_ROOM				14
#define CREATE_CHATROOM             17
#define PRINT_ROOMS                 18
#define LOG_IN						7
#define SIGN_UP                     8
#define REJECT                      9
#define NOT_A					    10
#define PRINT_USER_LIST             11
#define PRINT_USER_CONNECTED        12
#define CREATE_CHAT_ROOM			13
#define CLOSE_CHAT_ROOM				14
#define PRINT_CHAT_ROOM             18
#define OPEN_SESSION_WITH_CHAT_ROOM 19
#define PRINT_USER_IN_ROOM          20
#define GET_STATUS                  21
#define EXIT_FROM_ROOM              22
#define EXIT_FROM_ROOM_NOT_SUCCESS  23
#define CLOSE_ROOM                  24
#define ERROR_OWNER  				25
#define ROOM_NOT_FOUND              26
#define EXIT_FROM_ROOM_SUCCESS      27
#define ERASE_MSG                   28
#define USER_NOT_FOUND              29
#define USER_BUSY					30
#define LOGIN_NOT_SUCCESS           31
#define DISCONECT                   32
#define ROOM_IS_EXIST               33
#define USER_IS_EXIST               34

using namespace std;
class TCPMessengerProtocol{
public:
/*
 * Sends data
 */
void static sendData(TCPSocket* sock, string data)
{
	int add = htonl (data.length());

	if (sock->send((char*)&add, 4) < 0)
	{
		perror("fail to send data length");
	}

	if (sock->send(data.data(),data.length()) < 0)
	{
		perror("fail to send data");
	}
}
/*
 * Sends command through socket
 */
void static sendCommand(TCPSocket* sock, int command)
{
	command = htonl(command);
	sock->send((char*)&command,4);
}
/*
 * Reads command from socket
 */
int static readCommand(TCPSocket* sock)
{
	int command = 0;
	if(sock->recv((char*)&command,4)<0)
	{
		perror("failed to read command");
	}
	command = ntohl(command);
	return command;
}
/*
 * Reads data from socket
 */
string static readData(TCPSocket* sock)
{
	char buffer[100];
	int len;
	len = 0;
	memset((void*)buffer,0,100);
	sock->recv((char*)&len,4);
	len = ntohl(len);
	sock->recv(buffer, len);
	string Data(buffer);
	return Data;
}

/*
 * Reads data from socket
 */
void static readFromSocket(int length , TCPSocket * p)
{
	cout<<"The results are: "<<endl;
	int i = 0;
	for(i = 0 ; i < length ; i++)
	{
		string Index = TCPMessengerProtocol::readData(p);
		cout<<Index<<endl;
	}

}

};
#endif /* TCPMESSENGERPROTOCOL_H_ */

