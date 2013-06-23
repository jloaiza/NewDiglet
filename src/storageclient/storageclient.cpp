#include "storageclient.h"

StorageClient::StorageClient(std::string pIp, int pPort)
{
    _ip = pIp;
    _port = pPort;
}

std::string StorageClient::Connect(std::string pDiskID, std::string pSecurityKeyMD5)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("connect ") + std::string("<") + std::string(pDiskID) + std::string("> ") + std::string("<") + std::string(pSecurityKeyMD5) + std::string(">");
    std::cout << "vamos a leer" << std::endl;
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;
}

std::string StorageClient::getFreeBlock(std::string pDiskID)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("getFreeBlock ") + std::string("<") + std::string(pDiskID) + std::string(">");
    client->sendMessage(message);
    std::string messagea =  client->readMessage();
    delete client;
    return messagea;
}

std::string StorageClient::readBlock(std::string pDiskID, std::string pBlock)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("readBlock ") + std::string("<") + std::string(pDiskID) + std::string("> ") + std::string("<") + std::string(pBlock) + std::string(">");
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea; 
}

std::string StorageClient::writeBlock(std::string pDiskID, std::string pBlock, std::string pData)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("writeBlock ") + std::string("<") + std::string(pDiskID) + std::string("> ") + std::string("<") + std::string(pBlock) + std::string("> ") + std::string("<") + std::string(pData) + std::string(">");
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
    std::string message = std::string("getDiskSize ") + std::string("<") + std::string(pDiskID) + std::string(">");
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;
}

std::string StorageClient::writeBytes(std::string pDiskID, std::string pBlock, std::string pOffSet, std::string pSize, std::string pData)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("writeBytes ") + std::string("<") + std::string(pDiskID) + std::string("> ") + std::string("<") + std::string(pBlock) + std::string("> ") + std::string("<") + std::string(pOffSet) + std::string("> ") + std::string("<") + std::string(pSize) + std::string("> ") + std::string("<") + std::string(pData) + std::string(">");
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;
}

std::string StorageClient::readBytes(std::string pDiskID, std::string pBlock, std::string pOffSet, std::string pSize)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    std::string message = std::string("readBytes ") + std::string("<") + std::string(pDiskID) + std::string("> ") + std::string("<") + std::string(pBlock) + std::string("> ") + std::string("<") + std::string(pOffSet) + std::string("> ") + std::string("<") + std::string(pSize) + std::string(">");
    client->sendMessage(message);
    std::string messagea = client->readMessage();
    delete client;
    return messagea;
}