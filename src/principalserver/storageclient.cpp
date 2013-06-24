#include "storageclient.h"

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
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;
}

std::string StorageClient::getFreeBlock(std::string pDiskID)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("getFreeBlock ") + std::string(pDiskID);
    client->sendMessage(message);
    std::string messagea =  client->readMessage();
    delete client;
    return messagea;
}

std::string StorageClient::readBlock(std::string pDiskID, int pBlock)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("readBlock ") + std::string(pDiskID) + std::string(" ") + std::to_string(pBlock);
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea; 
}

std::string StorageClient::writeBlock(std::string pDiskID, int pBlock, std::string pData)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("writeBlock ") + std::string(pDiskID) + std::string(" ") + std::to_string(pBlock) + std::string(" ") + std::string(pData);
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

std::string StorageClient::getDiskSize(std::string pDiskID)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("getDiskSize ") + std::string(pDiskID);
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

std::string StorageClient::writeBytes(int pDiskID, int pBlock, int pOffSet, std::string pSize, std::string pData)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("writeBytes ") + std::to_string(pDiskID) + std::string(" ") + std::to_string(pBlock) + std::string(" ") + std::to_string(pOffSet) + std::string(" ") + std::to_string(pSize) + std::string(" ") + std::string(pData);
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;
}

std::string StorageClient::readBytes(int pDiskID, int pBlock, int pOffSet, std::string pSize)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("readBytes ") + std::string(pDiskID) + std::string(" ") + std::string(pBlock) + std::string(" ") + std::string(pOffSet) + std::string(" ") + std::string(pSize);
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;
}

bool StorageClient::isAlive(std::string pDiskID)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string(pDiskID);
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
    Disk* disk = _diskList->search(pDisk);
    return disk;
}