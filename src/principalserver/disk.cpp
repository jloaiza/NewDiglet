#include "disk.h"

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

Disk::Disk(StorageClient* pClient, int pID, std::string pSecKey){
	_storageClient = pClient;
	_id = pID;
	_secKey = pSecKey;
	_storageClient->connect(pID, pSecKey);
	_storageClient->addDisk(this);
}

std::string Disk::readBlock(int pBlock){
	return _storageClient->readBlock(_id, pBlock);
}

int Disk::writeBlock(std::string pData, int pBlock){
	return (_storageClient->writeBlock(_id, pBlock, pData)==""?0:1);
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