#include "lssoperations.h"
#include "lssmanager.h"
#include "session.h"
#include "lss.h"
#include <iostream>

int LssOperations::newSession(){
	LssManager* manager = LssManager::getInstance();
	return manager->newSession();
}

std::string LssOperations::getSize(short pID, int pSessionID){
	LssManager* manager = LssManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	Lss* lss = session->getLss(pID);
	if (lss == 0){
		return "?Error. El disco no ha sido encontrado\n";
	} else {
		return std::to_string(lss->getDiskSize());
	}
}

std::string LssOperations::format(short pID, int pSessionID, int pBlockSize){
	LssManager* manager = LssManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	Lss* lss = session->getLss(pID);
	if (lss == 0){
		return "?Error. El disco no ha sido encontrado\n";
	} else {
		lss->format(pBlockSize);
		return "formated.";
	}
}

std::string LssOperations::isAlive(short pID){
	LssManager* manager = LssManager::getInstance();
	std::cout<<"isAlive request. Disk: '"<<pID<<"' alive: "<<(manager->getLss(pID) != 0?"true":"false")<<std::endl;
	return (manager->getLss(pID)) != 0?"true":"false";
}

std::string LssOperations::connect(short pID, std::string pKey, int pSessionID){
	LssManager* manager = LssManager::getInstance();
	Lss* toAdd = manager->getLss(pID);
	if (toAdd == 0){
		return "?Error. El disco no ha sido encontrado\n";
	}
	if (toAdd->getSecKey() != pKey){
		return "?Error. Security key incorrecta\n";
	}
	Session* session = manager->getSession(pSessionID);
	if (toAdd->isBusy()){
		return "?Error. El disco ya está en uso\n";
	} else {
		session->addLss(toAdd);
		return "Connected.\n";
	}
}

std::string LssOperations::readBlock(short pID, int pBlock, int pSessionID){
	LssManager* manager = LssManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	Lss* lss = session->getLss(pID);
	if (lss == 0){
		return "?Error. El disco no ha sido encontrado\n";
	}
	return lss->readA(pBlock);
}

std::string LssOperations::writeBlock(short pID, std::string pData, int pSessionID){
	std::cout<<"to write: "<< pData<<std::endl;
	LssManager* manager = LssManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	Lss* lss = session->getLss(pID);
	if (lss == 0){
		return "?Error. El disco no ha sido encontrado\n";
	}
	return std::to_string(lss->writeA(pData));
}

std::string LssOperations::writeBytes(short pID, int pBlock, int pOffset, int pSize, std::string pData, int pSessionID){
	std::cout<<"to write: "<< pData<<std::endl;
	LssManager* manager = LssManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	Lss* lss = session->getLss(pID);
	if (lss == 0){
		return "?Error. El disco no ha sido encontrado\n";
	}
	lss->writeC(pData, pBlock, pOffset, pSize);
	return "Wrote.";
}

std::string LssOperations::readBytes (short pID, int pBlock, int pOffset, int pSize, int pSessionID){
	LssManager* manager = LssManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	Lss* lss = session->getLss(pID);
	if (lss == 0){
		return "?Error. El disco no ha sido encontrado\n";
	}
	return lss->readC(pBlock, pOffset, pSize);
}
