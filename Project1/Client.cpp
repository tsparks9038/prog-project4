#define _CRT_SECURE_NO_WARNINGS
#include <windows.networking.sockets.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Packet.h"

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

struct userInfo
{

	//user details
	string userID;
	string firstName;
	string lastName;
	string userName;
	string userPass;
	string socialOne;
	string socialTwo;
	string socialThree;
	string socialFour;

	//Booleans for genre selection
	string addSandbox;
	string addFPS;
	string addRTS;
	string addMOBA;
	string addRPG;
	string addSim;
	string addPuzzle;
	string addActionAdventure;
	string addSurvivalHorror;
	string addPlatformer;
};

void displayUserList(userInfo userList[10]);
void displaySingleUser(userInfo* theUser);
void changeUserInfo(userInfo* theUser);
void displayUserMenu(userInfo* theUser);

int main()
{
	//starts Winsock DLLs
	WSADATA wsaData;
	if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		return 0;
	}

	//initializes socket. SOCK_STREAM: TCP
	SOCKET ClientSocket;
	ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ClientSocket == INVALID_SOCKET) {
		WSACleanup();
		return 0;
	}

	//Connect socket to specified server
	sockaddr_in SvrAddr;
	SvrAddr.sin_family = AF_INET;						//Address family type itnernet
	SvrAddr.sin_port = htons(27000);					//port (host to network conversion)
	SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	//IP address
	if ((connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
		closesocket(ClientSocket);
		WSACleanup();
		return 0;
	}

	//Hardcoded guest password for the system
	string guestPass = "letmein";
	string guestName = "Guest";
	char userSelect;
	char guestSelect;
	char menuSelect;
	int i, j, k;
	int fileSize = 0;
	string userName;
	string userPassword;
	Packet pkt;
	char* TxBuffer = new char[dataLength];
	char* RxBuffer = new char[dataLength];
	userInfo userList[10];
	char test[6] = { "blank" };

	RxBuffer = new char[dataLength];

	pkt.setSource(0);
	pkt.setDestination(1);
	pkt.setID(0);
	pkt.setData(test, strlen(test));

	TxBuffer = new char[14];

	TxBuffer = pkt.SerializeData();

	send(ClientSocket, TxBuffer, dataLength, 0);
	recv(ClientSocket, RxBuffer, dataLength, 0);

	Packet newPkt(RxBuffer);
	istringstream pktData(newPkt.getData());

	for (int i = 0; i < 10; i++) {
		getline(pktData, userList[i].userID);
		getline(pktData, userList[i].firstName);
		getline(pktData, userList[i].lastName);
		getline(pktData, userList[i].userName);
		getline(pktData, userList[i].userPass);
		getline(pktData, userList[i].socialOne);
		getline(pktData, userList[i].socialTwo);
		getline(pktData, userList[i].socialThree);
		getline(pktData, userList[i].socialFour);

		getline(pktData, userList[i].addSandbox);
		getline(pktData, userList[i].addFPS);
		getline(pktData, userList[i].addRTS);
		getline(pktData, userList[i].addMOBA);
		getline(pktData, userList[i].addRPG);
		getline(pktData, userList[i].addSim);
		getline(pktData, userList[i].addPuzzle);
		getline(pktData, userList[i].addActionAdventure);
		getline(pktData, userList[i].addSurvivalHorror);
		getline(pktData, userList[i].addPlatformer);
	}
	
	do
	{
		TxBuffer = new char[dataLength];
		RxBuffer = new char[dataLength];
		
		cout << "Hello, please select from one of the following options.\n";
		cout << "A) Log in as a user.\n";
		cout << "B) Log in as a guest.\n";
		cout << "C) Quit.\n";
		cout << "Your selection: ";

		cin >> userSelect;

		//cout << "Your selection: " << userSelect << "\n";

		menuSelect = toupper(userSelect);

		switch (menuSelect)
		{

		case('A'):
			cout << "User Login Menu.\n";
			cout << "Please input your username and password.\n";
			cout << "Username: ";
			cin >> userName;
			cout << "Password: ";
			cin >> userPassword;


			if (userName == userList[0].userName && userPassword == userList[0].userPass)
			{
				displayUserMenu(&userList[0]);
			}
			else if (userName == userList[1].userName && userPassword == userList[1].userPass)
			{
				displayUserMenu(&userList[1]);
			}
			else if (userName == userList[2].userName && userPassword == userList[2].userPass)
			{
				displayUserMenu(&userList[2]);
			}
			else if (userName == userList[3].userName && userPassword == userList[3].userPass)
			{
				displayUserMenu(&userList[3]);
			}
			else if (userName == userList[4].userName && userPassword == userList[4].userPass)
			{
				displayUserMenu(&userList[4]);
			}
			else if (userName == userList[5].userName && userPassword == userList[5].userPass)
			{
				displayUserMenu(&userList[5]);
			}
			else if (userName == userList[6].userName && userPassword == userList[6].userPass)
			{
				displayUserMenu(&userList[6]);
			}
			else if (userName == userList[7].userName && userPassword == userList[7].userPass)
			{
				displayUserMenu(&userList[7]);
			}
			else if (userName == userList[8].userName && userPassword == userList[8].userPass)
			{
				displayUserMenu(&userList[8]);
			}
			else if (userName == userList[9].userName && userPassword == userList[9].userPass)
			{
				displayUserMenu(&userList[9]);
			}
			else
			{
				cout << "Sorry, that username/password combination does not match any of our users.\n";
			}

			break;

		case('B'):
			cout << "Guest Login Menu.\n";
			cout << "Please input the guest credentials.\n";
			cout << "Guest Username: ";
			cin >> userName;
			cout << "Guest Password: ";
			cin >> userPassword;

			if (userName == guestName && userPassword == guestPass)
			{
				cout << "Welcome guest. Please choose from one of the following options.\n";
				cout << "A) Display User List\n";
				cout << "B) Back to Main Menu\n";
				cout << "Your selection: ";

				cin >> guestSelect;

				guestSelect = toupper(guestSelect);

				switch (guestSelect)
				{
				case('A'):
					displayUserList(userList);

				case('B'):
					break;
				}


			}
			else
			{
				cout << "Invalid guest username/password. Please try again.\n";
			}

			break;

		case('C'):

			cout << "Quitting program, goodbye...\n";
			break;

		default:

			cout << "Invalid selection, please try again.";

		}

	} while (menuSelect != 'C');

	Packet pktUpdate;
	string userStr;
	for (int i = 0; i < 10; i++)	//dont append
	{
		userStr = userList[i].userID;
		userStr.append(userList[i].firstName);
		userStr.append(userList[i].lastName);
		userStr.append(userList[i].userName);
		userStr.append(userList[i].userPass);
		userStr.append(userList[i].socialOne);
		userStr.append(userList[i].socialTwo);
		userStr.append(userList[i].socialThree);
		userStr.append(userList[i].socialFour);
		userStr.append(userList[i].addSandbox);
		userStr.append(userList[i].addFPS);
		userStr.append(userList[i].addRTS);
		userStr.append(userList[i].addMOBA);
		userStr.append(userList[i].addRPG);
		userStr.append(userList[i].addSim);
		userStr.append(userList[i].addPuzzle);
		userStr.append(userList[i].addActionAdventure);
		userStr.append(userList[i].addSurvivalHorror);
		userStr.append(userList[i].addPlatformer);
	}

	char* userCharPtr = new char[userStr.length() + 1];
	strncpy(userCharPtr, userStr.c_str(), userStr.length());

	pktUpdate.setID(1);
	pktUpdate.setSource(0);
	pktUpdate.setDestination(1);
	pktUpdate.setData(userCharPtr, sizeof(userCharPtr));

	if(TxBuffer)
		delete[] TxBuffer;

	TxBuffer = new char[dataLength];

	TxBuffer = pktUpdate.SerializeData();

	send(ClientSocket, TxBuffer, sizeof(TxBuffer), 0);

	//closes connection and socket
	closesocket(ClientSocket);

	//frees Winsock DLL resources
	WSACleanup();

	return 1;
}

void displayUserList(userInfo userList[10])
{
	int i;
	bool hasPSX;
	bool hasXBOX;
	bool hasSwitch;
	bool hasPC;

	bool playsSandbox;
	bool playsFPS;
	bool playsRTS;
	bool playsMOBA;
	bool playsRPG;
	bool playsSim;
	bool playsPuzzle;
	bool playsAction;
	bool playsHorror;
	bool playsPlatformer;

	int checkForBool;

	cout << "\nDisplaying User List...\n\n";

	for (i = 0; i < 10; i++)
	{
		cout << "User ID: " << i << "\n";
		//display user info
		//cout << "FirstName: " << userList[i].firstName << "\nLast Name: " << userList[i].lastName << "\n";
		cout << "Username: " << userList[i].userName << "\n";
		cout << "PSN: " << userList[i].socialOne << "\n";
		cout << "X-BOX Live: " << userList[i].socialTwo << "\n";
		cout << "Nintendo Friend Code: " << userList[i].socialThree << "\n";
		cout << "Steam Username: " << userList[i].socialFour << "\n";

		//check genres played
		checkForBool = stoi(userList[i].addSandbox);

		//Check if genre is selected
		if (checkForBool == 1)
		{
			playsSandbox = true;
		}
		else
		{
			playsSandbox = false;
		}

		checkForBool = stoi(userList[i].addFPS);

		if (checkForBool == 1)
		{
			playsFPS = true;
		}
		else
		{
			playsFPS = false;
		}


		checkForBool = stoi(userList[i].addRTS);

		if (checkForBool == 1)
		{
			playsRTS = true;
		}
		else
		{
			playsRTS = false;
		}

		checkForBool = stoi(userList[i].addMOBA);

		if (checkForBool == 1)
		{
			playsMOBA = true;
		}
		else
		{
			playsMOBA = false;
		}


		checkForBool = stoi(userList[i].addRPG);

		if (checkForBool == 1)
		{
			playsRPG = true;
		}
		else
		{
			playsRPG = false;
		}


		checkForBool = stoi(userList[i].addSim);

		if (checkForBool == 1)
		{
			playsSim = true;
		}
		else
		{
			playsSim = false;
		}


		checkForBool = stoi(userList[i].addPuzzle);

		if (checkForBool == 1)
		{
			playsPuzzle = true;
		}
		else
		{
			playsPuzzle = false;
		}


		checkForBool = stoi(userList[i].addActionAdventure);

		if (checkForBool == 1)
		{
			playsAction = true;
		}
		else
		{
			playsAction = false;
		}


		checkForBool = stoi(userList[i].addSurvivalHorror);

		if (checkForBool == 1)
		{
			playsHorror = true;
		}
		else
		{
			playsHorror = false;
		}


		checkForBool = stoi(userList[i].addPlatformer);

		if (checkForBool == 1)
		{
			playsPlatformer = true;
		}
		else
		{
			playsPlatformer = false;
		}

		cout << "Genres Played: \n";

		if (playsSandbox)
		{
			cout << "Sandbox\n";
		}

		if (playsSandbox)
		{
			cout << "Sandbox\n";
		}

		if (playsFPS)
		{
			cout << "First Person Shooters\n";
		}
		if (playsRTS)
		{
			cout << "Real Time Strategy\n";
		}
		if (playsMOBA)
		{
			cout << "Multiplayer Online Battle Arena\n";
		}
		if (playsRPG)
		{
			cout << "Role-Playing Games\n";
		}
		if (playsSim)
		{
			cout << "Simulations\n";
		}
		if (playsPuzzle)
		{
			cout << "Puzzles\n";
		}
		if (playsAction)
		{
			cout << "Action Adventure\n";
		}
		if (playsHorror)
		{
			cout << "Survival Horror\n";
		}
		if (playsPlatformer)
		{
			cout << "Platformers\n";
		}

		cout << "\n";
	}
}

void displaySingleUser(userInfo* theUser)
{

	bool hasPSX;
	bool hasXBOX;
	bool hasSwitch;
	bool hasPC;

	bool playsSandbox;
	bool playsFPS;
	bool playsRTS;
	bool playsMOBA;
	bool playsRPG;
	bool playsSim;
	bool playsPuzzle;
	bool playsAction;
	bool playsHorror;
	bool playsPlatformer;

	int checkForBool;

	//display single user's info
	cout << "User ID: " << theUser->userID << "\n";
	cout << "FirstName: " << theUser->firstName << "\nLast Name: " << theUser->lastName << "\n";
	cout << "Username: " << theUser->userName << "\n";
	cout << "Password: " << theUser->userPass << "\n";
	cout << "PSN: " << theUser->socialOne << "\n";
	cout << "X-BOX Live: " << theUser->socialTwo << "\n";
	cout << "Nintendo Friend Code: " << theUser->socialThree << "\n";
	cout << "Steam Username: " << theUser->socialFour << "\n";

	//check genres played
	checkForBool = stoi(theUser->addSandbox);

	//Check if genre is selected
	if (checkForBool == 1)
	{
		playsSandbox = true;
	}
	else
	{
		playsSandbox = false;
	}

	checkForBool = stoi(theUser->addFPS);

	if (checkForBool == 1)
	{
		playsFPS = true;
	}
	else
	{
		playsFPS = false;
	}


	checkForBool = stoi(theUser->addRTS);

	if (checkForBool == 1)
	{
		playsRTS = true;
	}
	else
	{
		playsRTS = false;
	}

	checkForBool = stoi(theUser->addMOBA);

	if (checkForBool == 1)
	{
		playsMOBA = true;
	}
	else
	{
		playsMOBA = false;
	}


	checkForBool = stoi(theUser->addRPG);

	if (checkForBool == 1)
	{
		playsRPG = true;
	}
	else
	{
		playsRPG = false;
	}


	checkForBool = stoi(theUser->addSim);

	if (checkForBool == 1)
	{
		playsSim = true;
	}
	else
	{
		playsSim = false;
	}


	checkForBool = stoi(theUser->addPuzzle);

	if (checkForBool == 1)
	{
		playsPuzzle = true;
	}
	else
	{
		playsPuzzle = false;
	}


	checkForBool = stoi(theUser->addActionAdventure);

	if (checkForBool == 1)
	{
		playsAction = true;
	}
	else
	{
		playsAction = false;
	}


	checkForBool = stoi(theUser->addSurvivalHorror);

	if (checkForBool == 1)
	{
		playsHorror = true;
	}
	else
	{
		playsHorror = false;
	}


	checkForBool = stoi(theUser->addPlatformer);

	if (checkForBool == 1)
	{
		playsPlatformer = true;
	}
	else
	{
		playsPlatformer = false;
	}

	cout << "Genres Played: \n";

	if (playsSandbox)
	{
		cout << "Sandbox\n";
	}

	if (playsFPS)
	{
		cout << "First Person Shooters\n";
	}
	if (playsRTS)
	{
		cout << "Real Time Strategy\n";
	}
	if (playsMOBA)
	{
		cout << "Multiplayer Online Battle Arena\n";
	}
	if (playsRPG)
	{
		cout << "Role-Playing Games\n";
	}
	if (playsSim)
	{
		cout << "Simulations\n";
	}
	if (playsPuzzle)
	{
		cout << "Puzzles\n";
	}
	if (playsAction)
	{
		cout << "Action Adventure\n";
	}
	if (playsHorror)
	{
		cout << "Survival Horror\n";
	}
	if (playsPlatformer)
	{
		cout << "Platformers\n";
	}

	cout << "\n";
}
void changeUserInfo(userInfo* theUser)
{
	char userSelect;
	char menuSelect;

	string updateInfo;

	do
	{
		cout << "Your Current Information: \n";
		//displaySingleUser(theUser);
		cout << "Please choose from one of the following options.\n\n";
		cout << "A) To update your Username. \n";
		cout << "B) To update your Password\n";
		cout << "C) To update your PSN.\n";
		cout << "D) To update your X-BOX Live.\n";
		cout << "E) To update your Nintendo Friend Code.\n";
		cout << "F) To update your Steam Username.\n";
		cout << "G) To toggle Sandbox genre. \n";
		cout << "H) To toggle First Person Shooter genre. \n";
		cout << "I) To toggle Real Time Strategy genre. \n";
		cout << "J) To toggle Multiplayer Online Battle Arena genre. \n";
		cout << "K) To toggle Role Playing Game genre. \n";
		cout << "L) To toggle Simulation genre. \n";
		cout << "M) To toggle Puzzle genre. \n";
		cout << "N) To toggle Action Adventure genre. \n";
		cout << "O) To toggle Survival Horror genre. \n";
		cout << "P) To toggle Platformer genre. \n";
		cout << "Q) To quit back to previous menu.\n";
		cout << "Your Selection: ";
		cin >> userSelect;

		menuSelect = toupper(userSelect);

		cout << "You chose " << menuSelect << "\n";

		switch (menuSelect)
		{
		case('A'):
			cout << "Enter your new username: ";
			cin >> updateInfo;
			theUser->userName = updateInfo;
			cout << "Your new username is: " << theUser->userName << "\n";
			break;
		case('B'):
			cout << "Enter your new Password: ";
			cin >> updateInfo;
			theUser->userPass = updateInfo;
			cout << "Your new password is: " << theUser->userPass << "\n";
			break;
		case('C'):
			cout << "Enter your new PSN: ";
			cin >> updateInfo;
			theUser->socialOne = updateInfo;
			cout << "Your new PSN is: " << theUser->socialOne << "\n";
			break;
		case('D'):
			cout << "Enter your new X-BOX Live: ";
			cin >> updateInfo;
			theUser->socialTwo = updateInfo;
			cout << "Your new X-BOX Live is: " << theUser->socialTwo << "\n";
			break;
		case('E'):
			cout << "Enter your new Nintendo Friend Code: ";
			cin >> updateInfo;
			theUser->socialThree = updateInfo;
			cout << "Your new Nintendo Friend Code is: " << theUser->socialThree << "\n";
			break;
		case('F'):
			cout << "Enter your new Steam Username: ";
			cin >> updateInfo;
			theUser->socialFour = updateInfo;
			cout << "Your new Steam Username is: " << theUser->socialFour << "\n";
			break;

		case('G'):
			if (theUser->addSandbox == "0")
			{
				theUser->addSandbox = "1";
				cout << "Adding Sandbox to genres played.\n";
			}
			else
			{
				theUser->addSandbox = "0";
				cout << "Removing Sandbox from genres played\n";

			}
			break;
		case('H'):
			if (theUser->addFPS == "0")
			{
				theUser->addFPS = "1";
				cout << "Adding First Person Shooters to genres played.\n";
			}
			else
			{
				theUser->addFPS = "0";
				cout << "Removing First Person Shooters from genres played.\n";
			}
			break;
		case('I'):
			if (theUser->addRTS == "0")
			{
				theUser->addRTS = "1";
				cout << "Adding Real Time Strategies to genres played.\n";
			}
			else
			{
				theUser->addRTS = "0";
				cout << "Removing Real Time Strategies from genres played.\n";
			}
			break;
		case('J'):
			if (theUser->addMOBA == "0")
			{
				theUser->addMOBA = "1";
				cout << "Adding Multiplayer Online Battle Arenas to genres played.\n";
			}
			else
			{
				theUser->addMOBA = "0";
				cout << "Removing Real Multiplayer Online Battle Arenas from genres played.\n";
			}
			break;
		case('K'):
			if (theUser->addRPG == "0")
			{
				theUser->addRPG = "1";
				cout << "Adding Role Playing Games to genres played.\n";
			}
			else
			{
				theUser->addRPG = "0";
				cout << "Removing Role Playing Games from genres played.\n";
			}
			break;
		case('L'):
			if (theUser->addSim == "0")
			{
				theUser->addSim = "1";
				cout << "Adding Simulations to genres played.\n";
			}
			else
			{
				theUser->addSim = "0";
				cout << "Removing Simulations from genres played.\n";
			}
			break;
		case('M'):
			if (theUser->addPuzzle == "0")
			{
				theUser->addPuzzle = "1";
				cout << "Adding Puzzles to genres played.\n";
			}
			else
			{
				theUser->addPuzzle = "0";
				cout << "Removing Puzzles from genres played.\n";
			}
			break;
		case('N'):
			if (theUser->addActionAdventure == "0")
			{
				theUser->addActionAdventure = "1";
				cout << "Adding Action/Adventure to genres played.\n";
			}
			else
			{
				theUser->addActionAdventure = "0";
				cout << "Removing Action/Adventure from genres played.\n";
			}
			break;
		case('O'):
			if (theUser->addSurvivalHorror == "0")
			{
				theUser->addSurvivalHorror = "1";
				cout << "Adding Survival/Horror to genres played.\n";
			}
			else
			{
				theUser->addSurvivalHorror = "0";
				cout << "Removing Survival/Horror from genres played.\n";
			}
			break;
		case('P'):
			if (theUser->addPlatformer == "0")
			{
				theUser->addPlatformer = "1";
				cout << "Adding Platformers to genres played.\n";
			}
			else
			{
				theUser->addPlatformer = "0";
				cout << "Removing Platformers from genres played.\n";
			}
			break;
		case('Q'):
			break;

		default:
			cout << "Invalid selection, please try again.\n";
			break;
		}


	} while (menuSelect != 'Q');
}
void displayUserMenu(userInfo* theUser)
{
	char userSelect;
	char menuSelect;

	do
	{
		cout << "Hello, " << theUser->userName << " please select from one of the following options.\n";
		cout << "A) View your info\n";
		cout << "B) Update your info.\n";
		cout << "C) Quit to Main Menu.\n";
		cout << "Your selection: ";

		cin >> userSelect;

		menuSelect = toupper(userSelect);

		switch (menuSelect)
		{
		case('A'):
			displaySingleUser(theUser);
			break;
		case('B'):
			cout << "Updating your info...\n";
			changeUserInfo(theUser);
			break;
		case('C'):
			"Qutting back to Main Menu\n";
			break;
		default:
			"Invalid selection, please try again.\n";
		}

	} while (menuSelect != 'C');
}