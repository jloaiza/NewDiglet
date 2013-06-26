#ifndef LSSNETWORKHANDLER
#define LSSNETWORKHANDLER

#include "../networkhandler/networkhandler.h"
#include "../structures/doublelinkedlist/doublelinkedlist.h"

#include "lssmanager.h"
#include "lss.h"

class LssManager;

class LSSNetworkHandler : public NetworkHandler
{
public:

	LSSNetworkHandler();

	void inMessage(std::string pMessage, int pSocket);

private:
	
	void connect(int pSocket, std::string pParam);
	void format(int pSocket, std::string pParam);
	void readBlock(int pSocket, std::string pParam);
	void writeBlock(int pSocket, std::string pParam);
	void getSize(int pSocket, std::string pParam);
	void writeBytes(int pSocket, std::string pParam);
	void readBytes(int pSocket, std::string pParam);
	void defaultCase(int pSocket, std::string pCommand);
};


#endif /* LSSNETWORKHANDLER */
