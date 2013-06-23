#ifndef STORAGECLIENT
#define STORAGECLIENT

#include "../clientcpp/client.h"
#include "../structures/doublelinkedlist/doublelinkedlist.h"
#include "disk.h"

class Disk;
class DoubleLinkedList;

class StorageClient
{
public:
    StorageClient(std::string pIp, int pPort);
    std::string connect(int pDiskID, std::string pSecurityKeyMD5);
    std::string getFreeBlock(int pDiskID);
    std::string readBlock(int pDiskID, int pBlock);
    std::string writeBlock(int pDiskID, std::string pBlock, std::string pData);
    std::string getLssList();
    std::string getDiskSize(int pDiskID);
    std::string writeBytes(int pDiskID, std::string pBlock, std::string pOffSet, std::string pSize, std::string pData);
    std::string readBytes(int pDiskID, std::string pBlock, std::string pOffSet, std::string pSize);
    std::string isAlive(std::string pDiskID);
    void addDisk(Disk* pDisk);
    Disk* getDisk(short pDisk);
    std::string getIP() const {return _ip;}
private:
    std::string _ip;
    int _port;
    DoubleLinkedList<Disk, short>* _diskList;
};

#endif /* STORAGECLIENT */