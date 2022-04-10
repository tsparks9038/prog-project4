#pragma once
#include <memory>
#include <iostream>
#include <fstream>

const int dataLength = 950;

class Packet
{
	struct Header
	{
		short sourceAddress;
		short destinationAddress;
		int packetID;
	} Head;

	char* Data;
	char* TxBuffer;

public:
	Packet() : Data(nullptr), TxBuffer(nullptr) { Head.sourceAddress = 0; };

	Packet(char* src)
	{
		memcpy(&Head, src, sizeof(Head));

		Data = new char[dataLength];

		memcpy(Data, src + sizeof(Head), dataLength);
	}

	short getSource() {
		return Head.sourceAddress;
	}
	void setSource(short source) {
		Head.sourceAddress = source;
	}
	short getDestination() {
		return Head.destinationAddress;
	}
	void setDestination(short destination) {
		Head.destinationAddress = destination;
	}
	int getID() {
		return Head.packetID;
	}
	void setID(short ID) {
		Head.packetID = ID;
	}

	void setData(char* srcData, int Size)
	{
		Data = new char[Size];

		memcpy(Data, srcData, Size);
	};

	char* getData()
	{
		return Data;
	};

	char* SerializeData()
	{
		if (TxBuffer) {
			delete[] TxBuffer;
		}

		int TotalPktSize = dataLength + sizeof(Head);
		TxBuffer = new char[TotalPktSize];

		memcpy(TxBuffer, &Head, sizeof(Head));
		memcpy(TxBuffer + sizeof(Head), Data, dataLength);

		return TxBuffer;
	};

};