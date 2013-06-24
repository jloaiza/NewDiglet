#include "storageclient.h"
#include "disk.h"

StorageClient::StorageClient(std::string pIp, int pPort)
{
    _ip = pIp;
    _port = pPort;
}

std::string StorageClient::connect(int pDiskID, std::string pSecurityKeyMD5)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("connect ") + std::to_string(pDiskID) + std::string(" ") + std::string(pSecurityKeyMD5);
    std::cout << "vamos a leer" << std::endl;
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;
}

std::string StorageClient::getFreeBlock(int pDiskID)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("getFreeBlock ") + std::to_string(pDiskID);
    client->sendMessage(message);
    std::string messagea =  client->readMessage();
    delete client;
    return messagea;
}

std::string StorageClient::readBlock(int pDiskID, int pBlock)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("readBlock ") + std::to_string(pDiskID) + std::string(" ") + std::to_string(pBlock);
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea; 
}

std::string StorageClient::writeBlock(int pDiskID, int pBlock, std::string pData)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("writeBlock ") + std::to_string(pDiskID) + std::string(" ") + std::to_string(pBlock) + std::string(" ") + std::string(pData);
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;    
}

std::string StorageClient::getLssList()
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("getLssList");
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;
}

std::string StorageClient::getDiskSize(int pDiskID)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("getDiskSize ") + std::to_string(pDiskID);
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;
}

bool StorageClient::isConnected(){
    Client* client = new Client(_ip,_port);
    client->Connect();
    bool connected = client->isConnect();
    delete client;
    return connected;
}

std::string StorageClient::writeBytes(int pDiskID, int pBlock, int pOffSet, int pSize, std::string pData)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("writeBytes ") + std::to_string(pDiskID) + std::string(" ") + std::to_string(pBlock) + std::string(" ") + std::to_string(pOffSet) + std::string(" ") + std::to_string(pSize) + std::string(" ") + std::string(pData);
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;
}

std::string StorageClient::readBytes(int pDiskID, int pBlock, int pOffSet, int pSize)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("readBytes ") + std::to_string(pDiskID) + std::string(" ") + std::to_string(pBlock) + std::string(" ") + std::to_string(pOffSet) + std::string(" ") + std::to_string(pSize);
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;
}

bool StorageClient::isAlive(int pDiskID)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::to_string(pDiskID);
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea != "";
}

void StorageClient::addDisk(Disk* pDisk)
{
    _diskList->insertEnd(pDisk);
}


Disk* StorageClient::getDisk(short pDisk)
{
    Disk* disk = _diskList->search(&pDisk);
    return disk;
}