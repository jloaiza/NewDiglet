#include "../clientcpp/client.h"

class StorageClient
{
public:
    StorageClient(std::string pIp, int pPort);
    std::string Connect(std::string pDiskID, std::string pSecurityKeyMD5);
    std::string getFreeBlock(std::string pDiskID);
    std::string readBlock(std::string pDiskID, std::string pBlock);
    std::string writeBlock(std::string pDiskID, std::string pBlock, std::string pData);
    std::string getLssList();
    std::string getDiskSize(std::string pDiskID);
    std::string writeBytes(std::string pDiskID, std::string pBlock, std::string pOffSet, std::string pSize, std::string pData);
    std::string readBytes(std::string pDiskID, std::string pBlock, std::string pOffSet, std::string pSize);
private:
    std::string _ip;
    int _port;
};