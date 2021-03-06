#ifndef STORAGECLIENT
#define STORAGECLIENT

#include "../clientcpp/client.h"
#include "../structures/doublelinkedlist/doublelinkedlist.h"

class Disk;

class StorageClient
{
public:

    bool operator==(std::string& pStorage){
        return _ip == pStorage;
    }
    bool operator!=(std::string& pStorage){
        return _ip != pStorage;
    }
    bool operator<=(std::string& pStorage){
        return _ip <= pStorage;
    }
    bool operator<(std::string& pStorage){
        return _ip < pStorage;
    }
    bool operator>=(std::string& pStorage){
        return _ip >= pStorage;
    }
    bool operator>(std::string& pStorage){
        return _ip > pStorage;
    }

    bool operator==(StorageClient& pStorage){
        return _ip == pStorage.getIP();
    }
    bool operator!=(StorageClient& pStorage){
        return _ip != pStorage.getIP();
    }
    bool operator<=(StorageClient& pStorage){
        return _ip <= pStorage.getIP();
    }
    bool operator<(StorageClient& pStorage){
        return _ip < pStorage.getIP();
    }
    bool operator>=(StorageClient& pStorage){
        return _ip >= pStorage.getIP();
    }
    bool operator>(StorageClient& pStorage){
        return _ip > pStorage.getIP();
    }


    StorageClient(std::string pIp, int pPort);
    std::string startClient();
    std::string connect(int pDiskID, std::string pSecurityKeyMD5);
    std::string readBlock(int pDiskID, int pBlock);
    int writeBlock(int pDiskID, std::string pData);
    std::string getDiskSize(int pDiskID);
    std::string format(int pDiskID, int pBlockSize);
    std::string writeBytes(int pDiskID, int pBlock, int pOffSet, int pSize, std::string pData);
    std::string readBytes(int pDiskID, int pBlock, int pOffSet, int pSize);
    bool isAlive(int pDiskID);
    void addDisk(Disk* pDisk);
    Disk* getDisk(short pDisk);
    std::string getIP() const {return _ip;}
    bool isConnected();
private:
    std::string _ip;
    int _port;
    int _sessionID;
    DoubleLinkedList<Disk, short>* _diskList;
    Client* _client;
};

#endif /* STORAGECLIENT */