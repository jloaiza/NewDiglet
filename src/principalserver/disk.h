#ifndef DISK
#define DISK

#include <string>
//#include "storageclient.h"
class StorageClient;

class Disk{
private:
	StorageClient* _storageClient;
	int _id;
	std::string _secKey;

public:
	bool operator==(std::string& pDisk);
	bool operator!=(std::string& pDisk);
	bool operator>(std::string& pDisk);
	bool operator>=(std::string& pDisk);
	bool operator<(std::string& pDisk);
	bool operator<=(std::string& pDisk);

	bool operator==(Disk& pDisk);
	bool operator!=(Disk& pDisk);
	bool operator>(Disk& pDisk);
	bool operator>=(Disk& pDisk);
	bool operator<(Disk& pDisk);
	bool operator<=(Disk& pDisk);

	Disk(StorageClient* pClient, int pID, std::string pSecKey);

	int getDiskID() const {
		return _id;
	}

	int getDiskDirection() const {
		return _storageClient->getIP() + ":" + _id;
	}

	bool isAlive();
	std::string readBlock(int pBlock);
	int writeBlock(std::string pData);
	void writeBytes(int pBlock, int pOffset, int pSize, std::string pData);
	std::string readBytes(int pBlock, int pOffset, int pSize);
};

#endif /* DISK */