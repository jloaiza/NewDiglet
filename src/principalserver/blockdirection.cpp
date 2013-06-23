#include "blockdirection.h"

BlockDirection::BlockDirection(char* pDir)
{
	setDirection(pDir);
}

char* BlockDirection::getDirection()
{
	return OriginalDirection;
}

void BlockDirection::setDirection(char* pDir)
{
	OriginalDirection = pDir;
	
	char* IP = new char[2];

	IP[0] = pDir[0];
	IP[1] = pDir[1];
	short IP1 = BytesHandler::to_ulong( BytesHandler::string2bin(std::string(IP, 2), 2) );
	
	IP[0] = pDir[2];
	IP[1] = pDir[3];
	short IP2 = BytesHandler::to_ulong( BytesHandler::string2bin(std::string(IP, 2), 2) );

	IP[0] = pDir[4];
	IP[1] = pDir[5];
	short IP3 = BytesHandler::to_ulong( BytesHandler::string2bin(std::string(IP, 2), 2) );

	_IP = std::to_string(IP1) + "." + std::to_string(IP2) + "." + std::to_string(IP3); 

	IP[0] = pDir[6];
	IP[1] = pDir[7];
	_disk = BytesHandler::to_ulong( BytesHandler::string2bin(std::string(IP, 2), 2) );
	
	IP[0] = pDir[8];
	IP[1] = pDir[9];
	_block = BytesHandler::to_ulong( BytesHandler::string2bin(std::string(IP, 2), 2) );
	
	delete[] IP;
}

std::string BlockDirection::getIP()
{
	return _IP;
}
	
short BlockDirection::getDisk()
{
	return _disk;
}

short BlockDirection::getBlock()
{
	return _block;	
}
