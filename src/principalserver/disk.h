#ifndef DISK
#define DISK

#include <string>

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

	bool operator==(short& pDisk);
	bool operator!=(short& pDisk);
	bool operator>(short& pDisk);
	bool operator>=(short& pDisk);
	bool operator<(short& pDisk);
	bool operator<=(short& pDisk);

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

	std::string getDiskDirection();

	std::string getIp();
	bool isAlive();
	void format(int pBlockSize);
	std::string readBlock(int pBlock);
	int writeBlock(std::string pData);
	void writeBytes(int pBlock, int pOffset, int pSize, std::string pData);
	std::string readBytes(int pBlock, int pOffset, int pSize);
};

#endif /* DISK */