#include "lssmanager.h"
#include "../structures/doublelinkedlist/listnode.h"
#include "lssconsole.h"
#include "lssnetworkhandler.h"
#include <iostream>

LssManager* LssManager::_instance = 0;

LssManager::LssManager(){ 
	_console = new LssConsole(this);
	_networkHandler = new LSSNetworkHandler();
	_lss = new DoubleLinkedList<Lss, short>();
	_sessions = new DoubleLinkedList<Session, int>();
	_lssCount = 0;
	_instance = this;
}

int LssManager::newSession(){
	Session* session = new Session();
	_sessions->insertEnd(session);
	return session->getID();
}

Session* LssManager::getSession(int pSessionID){
	return _sessions->search(&pSessionID);
}

Lss* LssManager::getLss(short pID){
	return _lss->search(&pID);
}

LssManager* LssManager::getInstance(){
	return _instance;
}

void LssManager::createDisk(int pFileSize, std::string pSecKey){
	Lss* lss = new Lss(std::to_string(_lssCount), _lssCount, pFileSize, pSecKey);
	_lss->insertEnd(lss);
	_lssCount++;
}

void LssManager::eraseDisk(short pID, std::string pSecKey){
	if (_lss->search(&pID) != 0){
		delete _lss->erase(&pID);
	}
}


void LssManager::saveDisks(){

}

void LssManager::startSystem(){
	std::cout<<"console"<<std::endl;
	_console->start();
	_networkHandler->start();
	_console->getThread()->join();
	_networkHandler->getThread()->join();
}

void LssManager::stopSystem(){
	saveDisks();
	_console->stop();
	_networkHandler->closeServer();
}

void LssManager::showDisks(){
	ListNode<Lss>* iNode = _lss->getHead();
	while (iNode != 0){
		std::cout<<(*iNode->getData());
		if (iNode->getNext() != 0){
			std::cout<<" - ";
		}
		iNode = iNode->getNext();
	}
	std::cout<<std::endl;
}
