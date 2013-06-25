#include "disk.h"
#include "storageclient.h"

bool Disk::operator==(std::string& pDisk){
	return getDiskDirection() == pDisk;
}

bool Disk::operator!=(std::string& pDisk){
	return getDiskDirection() != pDisk;
}

bool Disk::operator>(std::string& pDisk){
	return getDiskDirection() > pDisk;
}

bool Disk::operator>=(std::string& pDisk){
	return getDiskDirection() >= pDisk;
}

bool Disk::operator<(std::string& pDisk){
	return getDiskDirection() < pDisk;
}

bool Disk::operator<=(std::string& pDisk){
	return getDiskDirection() <= pDisk;
}

bool Disk::operator==(Disk& pDisk){
	return getDiskDirection() == pDisk.getDiskDirection();
}

bool Disk::operator!=(Disk& pDisk){
	return getDiskDirection() != pDisk.getDiskDirection();
}

bool Disk::operator>(Disk& pDisk){
	return getDiskDirection() > pDisk.getDiskDirection();
}

bool Disk::operator>=(Disk& pDisk){
	return getDiskDirection() >= pDisk.getDiskDirection();
}

bool Disk::operator<(Disk& pDisk){
	return getDiskDirection() < pDisk.getDiskDirection();
}

bool Disk::operator<=(Disk& pDisk){
	return getDiskDirection() <= pDisk.getDiskDirection();
}

bool Disk::operator==(short& pDisk){
	return _id == pDisk;
}

bool Disk::operator!=(short& pDisk){
	return _id != pDisk;
}

bool Disk::operator>(short& pDisk){
	return _id > pDisk;
}

bool Disk::operator>=(short& pDisk){
	return _id >= pDisk;
}

bool Disk::operator<(short& pDisk){
	return _id < pDisk;
}

bool Disk::operator<=(short& pDisk){
	return _id <= pDisk;
}

Disk::Disk(StorageClient* pClient, int pID, std::string pSecKey){
	_storageClient = pClient;
	_id = pID;
	_secKey = pSecKey;
	_storageClient->connect(pID, pSecKey);
	_storageClient->addDisk(this);
}

std::string Disk::getDiskDirection() {
		return _storageClient->getIP() + std::string(":") + std::to_string(_id);
	}

std::string Disk::readBlock(int pBlock){
	return _storageClient->readBlock(_id, pBlock);
}

int Disk::writeBlock(std::string pData){
	return _storageClient->writeBlock(_id, pData);
}

void Disk::writeBytes(int pBlock, int pOffset, int pSize, std::string pData){
	_storageClient->writeBytes(_id, pBlock, pOffset, pSize, pData);
}

std::string Disk::readBytes(int pBlock, int pOffset, int pSize){
	return _storageClient->readBytes(_id, pBlock, pOffset, pSize);
}

bool Disk::isAlive(){
	return _storageClient->isConnected() && _storageClient->isAlive(_id);
}