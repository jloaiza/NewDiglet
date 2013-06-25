
#ifndef LSSOPERATIONS
#define LSSOPERATIONS

#include <string>

class LssOperations {
	
public:
	static int newSession();
	static std::string getSize(short pID, int pSessionID);
	static std::string connect(short pID, std::string pKey, int pSessionID);
	static std::string readBlock(short pID, int pBlock, int pSessionID);
	static std::string writeBlock(short pID, std::string pData, int pSessionID);
	static std::string writeBytes(short pID, int pBlock, int pOffset, int pSize, std::string pData, int pSessionID);
	static std::string readBytes (short pID, int pBlock, int pOffset, int pSize, int pSessionID);

};
#endif
