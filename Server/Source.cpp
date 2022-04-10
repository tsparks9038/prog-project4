#include <windows.networking.sockets.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../Project1/Packet.h"

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int main()
{
	//starts Winsock DLLs		
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	//create server socket
	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ServerSocket == INVALID_SOCKET) {
		WSACleanup();
		return 0;
	}

	//binds socket to address
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;
	SvrAddr.sin_addr.s_addr = INADDR_ANY;
	SvrAddr.sin_port = htons(27000);
	if (bind(ServerSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr)) == SOCKET_ERROR)
	{
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}

	//listen on a socket
	if (listen(ServerSocket, 1) == SOCKET_ERROR) {
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}


	cout << "Waiting for client connection\n" << endl;

	//accepts a connection from a client
	SOCKET ConnectionSocket;
	ConnectionSocket = SOCKET_ERROR;
	if ((ConnectionSocket = accept(ServerSocket, NULL, NULL)) == SOCKET_ERROR) {
		closesocket(ServerSocket);
		WSACleanup();
		return 0;
	}

	cout << "Connected, waiting for transfer...\n" << endl;

	char* RxBuffer = new char[dataLength];

	recv(ConnectionSocket, RxBuffer, dataLength, 0);

	Packet pkt(RxBuffer);

	if (pkt.getID() == 0) {
		ifstream userFile("UserInfo.txt");
		Packet pktFile;

		if (!userFile)
		{
			cout << "Could not find user info file";
		}

		else {
			userFile.seekg(0, ios::end);
			size_t fileSize = userFile.tellg();

			char* fileData = new char[fileSize];

			userFile.seekg(0, ios::beg);
			userFile.read(fileData, fileSize);

			if (userFile.eof()) {
				size_t bytes_read = userFile.gcount();
			}

			else if (userFile.fail()) {

			}

			userFile.close();

			pktFile.setSource(1);
			pktFile.setDestination(0);
			pktFile.setID(0);
			pktFile.setData(fileData, strlen(fileData));

			int size = strlen(fileData) + 8;
			char* TxBuffer = new char[size];

			TxBuffer = pktFile.SerializeData();

			send(ConnectionSocket, TxBuffer, dataLength, 0);
		}
	}

	else if (pkt.getID() == 1) {
		ofstream userFile("UserInfo.txt");

		userFile << pkt.getData();

		userFile.close();
	}

	else {
		ifstream profPic("pic.jpg");
		Packet pktPic;

		if (!profPic)
		{
			cout << "Could not find profile picture";
		}

		else {
			profPic.seekg(0, ios::end);
			size_t fileSize = profPic.tellg();

			char* fileData = new char[fileSize];

			profPic.seekg(0, ios::beg);
			profPic.read(fileData, fileSize);

			if (profPic.eof()) {
				size_t bytes_read = profPic.gcount();
			}

			else if (profPic.fail()) {

			}

			profPic.close();

			pktPic.setSource(1);
			pktPic.setDestination(0);
			pktPic.setID(2);
			pktPic.setData(fileData, strlen(fileData));

			int size = strlen(fileData) + 8;
			char* TxBuffer = new char[size];

			cout << strlen(fileData);

			TxBuffer = pktPic.SerializeData();

			send(ConnectionSocket, TxBuffer, size, 0);
		}
	}

	closesocket(ConnectionSocket);	//closes incoming socket
	closesocket(ServerSocket);	    //closes server socket	
	WSACleanup();					//frees Winsock resources

	return 1;
}