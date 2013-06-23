#ifndef STORAGECLIENT
#define STORAGECLIENT

#include "../clientcpp/client.h"

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
    std::string getIP() const {
        return _ip;
    }
private:
    std::string _ip;
    int _port;
};

#endif /* STORAGECLIENT */