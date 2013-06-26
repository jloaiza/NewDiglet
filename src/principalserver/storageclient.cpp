#include "storageclient.h"
#include "disk.h"

StorageClient::StorageClient(std::string pIp, int pPort)
{
    _ip = pIp;
    _port = pPort;
    _diskList = new DoubleLinkedList<Disk, short>();
    startClient();
}


std::string StorageClient::startClient()
{
    Client* client = new Client(_ip, _port);
    client->Connect();

    std::string message = std::string("startClient");

    client->sendMessage(message);
    std::string messagea = client->readMessage();
    _sessionID = std::stoi(messagea);
    delete client;
    return messagea;
}

std::string StorageClient::format(int pDiskID, int pBlockSize)
{
    Client* client = new Client(_ip, _port);
    client->Connect();

    std::string message = std::string("format ") + std::to_string(pDiskID) + std::string(" ") + std::to_string(_sessionID) + std::string(" ") + std::to_string(pBlockSize);

    client->sendMessage(message);
    std::string messagea = client->readMessage();
    _sessionID = std::stoi(messagea);
    delete client;
    return messagea;
}

std::string StorageClient::connect(int pDiskID, std::string pSecurityKeyMD5)
{
    Client* client = new Client(_ip,_port);
    client->Connect();

    std::string message = std::string("connect ") + std::to_string(_sessionID) + std::string(" ")  + std::to_string(pDiskID) + std::string(" ") + std::string(pSecurityKeyMD5);

    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;
}



std::string StorageClient::readBlock(int pDiskID, int pBlock)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("readBlock ") + std::to_string(_sessionID) + std::string(" ") + std::to_string(pDiskID) + std::string(" ") + std::to_string(pBlock);
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea; 
}

int StorageClient::writeBlock(int pDiskID, std::string pData)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("writeBlock ") + std::to_string(_sessionID) + std::string(" ") + std::to_string(pDiskID) + std::string(" ") + std::string(pData);
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return std::stoi(messagea);
}

std::string StorageClient::getDiskSize(int pDiskID)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("getDiskSize ") + std::to_string(_sessionID) + std::string(" ") + std::to_string(pDiskID);
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
    std::string message = std::string("writeBytes ") + std::to_string(_sessionID) + std::string(" ") + std::to_string(pDiskID) + std::string(" ") + std::to_string(pBlock) + std::string(" ") + std::to_string(pOffSet) + std::string(" ") + std::to_string(pSize) + std::string(" ") + std::string(pData);
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;
}

std::string StorageClient::readBytes(int pDiskID, int pBlock, int pOffSet, int pSize)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("readBytes ")  + std::to_string(_sessionID) + std::string(" ") + std::to_string(pDiskID) + std::string(" ") + std::to_string(pBlock) + std::string(" ") + std::to_string(pOffSet) + std::string(" ") + std::to_string(pSize);
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;
}

bool StorageClient::isAlive(int pDiskID)
{
    return getDiskSize(pDiskID)[0] != '?';
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