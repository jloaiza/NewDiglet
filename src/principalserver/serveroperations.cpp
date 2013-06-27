#include "serveroperations.h"
#include "generalmanager.h"
#include "session.h"
#include "registerbuffer.h"
#include "datanode.h"
#include "databuffer.h"
#include "../include/constants.h"
#include "../structures/ntree/ntreenode.h"
#include "../tokenizer/tokenizer.h"
#include "../xml/usersxml.h"

#include <iostream>
#include <exception>

std::string ServerOperations::toCSV(DataNode* pData, RegisterSpace* pFormat){
	std::string data;
	DataNode* iNode = pData;

	while (iNode != 0){
		if (pData->getType() != PS::STRING_TYPE){
			if (pData->getType() != PS::DOUBLE_TYPE){
				data += std::to_string(*(long*)(pData->getData()));
			} else {
				data += std::to_string(*(double*)(pData->getData()));
			}
		} else {
			data += *(std::string*)(pData->getData());
		}
		iNode = pData->getNext();
	}
	
	data = data.substr(1, data.length()-1);

	int length;
	RegisterSpace* iSpace = pFormat;
	for (length; iSpace != 0; length++){
		iSpace = iSpace->getNext();
	}

	std::string csv;
	iSpace = pFormat;
	for (int i = 0; i < length; i ++){
		int lastComa = Tokenizer::charIndex(data, ',', length);
		csv += iSpace->getName() + std::string(",") + data.substr(0, lastComa) + std::string("\n");
		data = data.substr(lastComa+1, data.length()-lastComa-1);
	}
	return csv;
}

DataNode* ServerOperations::getData(std::string pData, RegisterSpace* pFormat){
	DataBuffer buffer;
	for (int i = 1; pFormat != 0; i++){
		int type = pFormat->getType();
		int size = pFormat->getSize();

		std::string dataSpace = Tokenizer::getCommandSpace(pData, i, '#');
		void* data = 0;

		if (dataSpace != ""){

			try{

				if (type != PS::STRING_TYPE){
					if (type == PS::SHORT_TYPE){
						data = new short(std::stoi(dataSpace));
					} else if(type == PS::INT_TYPE){
						data = new int(std::stoi(dataSpace));
					} else if(type == PS::LONG_TYPE){
						data = new long(std::stol(dataSpace));
					} else if(type == PS::DOUBLE_TYPE){
						data = new double(std::stod(dataSpace));
					}

				} else {
					data = new std::string(dataSpace);
				}

			} catch (std::exception e){
				return 0;
			}

		}
		
		buffer.addToBuffer(data, type, size);
		pFormat = pFormat->getNext();
	}
	return buffer.getBuffer();
}

RegisterSpace* ServerOperations::getFormat(std::string pFormat){
	bool splitting = true;
	RegisterBuffer buffer;
	try{
		for (int i = 1; splitting; i++){

			std::string formatSpace = Tokenizer::getCommandSpace(pFormat, i, ';');
			if (formatSpace != ""){

				std::string name = Tokenizer::getCommandSpace(formatSpace, 1, '#');
				int type = std::stoi(Tokenizer::getCommandSpace(formatSpace, 2, '#'));
				int size = std::stoi(Tokenizer::getCommandSpace(formatSpace, 3, '#'));
				buffer.addSpace(name, size, type);

			} else {
				splitting = false;
			}
		}
	} catch (std::exception e){
		return 0;
	}
	return buffer.getBuffer();
}
	
std::string ServerOperations::get(int pSessionID, std::string pPath){
	GeneralManager* manager = GeneralManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	if (session == 0){
		return "*Error. Sesión no encontrada\n";
	}
	DiskGroup* diskgroup = session->getDiskGroup();
	nTreeNode* currentNode = session->getCurrentNode();
	nTreeNode* toReadNode = diskgroup->getNode(pPath, currentNode);
	if (toReadNode == 0 || toReadNode->getFile() == 0){
		return "?Error. Archivo invalido\n";
	}
	DataNode* data = diskgroup->getFile(toReadNode->getFile());
	RegisterSpace* format = diskgroup->getRegFormat(toReadNode->getFile());
	return toCSV(data, format);
}

std::string ServerOperations::cd(int pSessionID, std::string pPath){
	GeneralManager* manager = GeneralManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	if (session == 0){
		return "*Error. Sesión no encontrada\n";
	}

	DiskGroup* diskgroup = session->getDiskGroup();
	nTreeNode* currentNode = session->getCurrentNode();

	std::cout<<"cd path: "<<pPath<<std::endl;

	nTreeNode* cdNode = diskgroup->getNode(pPath, currentNode);

	std::cout<<"cd node: "<<cdNode<<std::endl;

	if (cdNode == 0 || cdNode->getFile() != 0){
		return "?Error. Directorio invalido\n";
	}
	session->setCurrentNode(cdNode);
	return "";
}

std::string ServerOperations::rm(int pSessionID, std::string pPath){
	if (pPath == "./" || pPath == "/"){
		return "";
	}
	GeneralManager* manager = GeneralManager::getInstance();
	Session* session = manager->getSession(pSessionID);

	if (session == 0){
		return "*Error. Sesión no encontrada\n";
	}
	
	DiskGroup* diskgroup = session->getDiskGroup();
	nTreeNode* currentNode = session->getCurrentNode();
	nTreeNode* rmNode = diskgroup->getNode(pPath, currentNode);
	if (rmNode == 0){
		return "?Error. Ruta invalida\n";
	}
	diskgroup->deleteFile(rmNode);
	return "";
}

std::string ServerOperations::moveSeek(int pSessionID, int pSeekPos){
	GeneralManager* manager = GeneralManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	if (session == 0){
		return "*Error. Sesión no encontrada\n";
	}
	nTreeNode* currentNode = session->getCurrentNode();
	if (currentNode->getFile() == 0){
		return "?Error. No hay ningún archivo abierto\n";
	}
	if (currentNode->getFile()->getRegCount() < pSeekPos){
		return "?Error. El número de registro es invalido";
	}
	session->setSeek(pSeekPos);
	return "";
}

std::string ServerOperations::touch(int pSessionID, std::string pPath, std::string pFormat){
	std::cout<<"Touch h"<<std::endl;
	GeneralManager* manager = GeneralManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	if (session == 0){
		return "*Error. Sesión no encontrada\n";
	}
	std::cout<<"Touch h2"<<std::endl;
	DiskGroup* diskgroup = session->getDiskGroup();
	nTreeNode* currentNode = session->getCurrentNode();
	std::cout<<"Touch h2.1"<<std::endl;
	std::string fileName = Tokenizer::dividePathAndName(pPath, &pPath);
	std::cout<<"Touch h2.2"<<std::endl;
	if (haveRestringedChar(fileName)){
		return "?Error. El nombre contiene caracteres no permitidos\n";
	}
	std::cout<<"Touch h3"<<std::endl;
	nTreeNode* cdNode = diskgroup->getNode(pPath, currentNode);
	std::cout<<"Touch h3.1"<<std::endl;
	if (cdNode == 0 || cdNode->getFile() != 0){
		return "?Error. Ruta inválida\n";
	}
	std::cout<<"Touch h4"<<std::endl;
	RegisterSpace* format = getFormat(pFormat);
	session->setCurrentNode(diskgroup->createFile(cdNode, fileName, format, session->getUser()));
	session->setCurrentFormat(format);
	session->setSeek(0);
	return "";
}

bool ServerOperations::isRestringedChar(char pChar){
	char restringedChars[] = {'/', '\\', '"'};
	int length = (sizeof restringedChars)/sizeof(char);
	for (int i = 0; i < length; i++){
		if (pChar == restringedChars[i]){
			return true;
		}
	}
	return false;
}

bool ServerOperations::haveRestringedChar(std::string pEntry){
	for (int i = 0; i < pEntry.length(); i++){
		if ( isRestringedChar(pEntry[i]) ){
			return true;
		}
	}
	return false;;
}

std::string ServerOperations::mkdir(int pSessionID, std::string pName){
	if (haveRestringedChar(pName)){
		return "?Error. El nombre contiene caracteres no permitidos\n";
	}

	GeneralManager* manager = GeneralManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	if (session == 0){
		return "*Error. Sesión no encontrada\n";
	}
	DiskGroup* diskgroup = session->getDiskGroup();
	nTreeNode* currentNode = session->getCurrentNode();

	if (diskgroup->getNode(pName, currentNode) != 0){
		return "?Error. Ya existe un archivo o carpeta con el mismo nombre.";
	}

	diskgroup->createDir(currentNode, pName, session->getUser());
	return "";
}


std::string ServerOperations::ls(int pSessionID){
	GeneralManager* manager = GeneralManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	if (session == 0){
		return "*Error. Sesión no encontrada\n";
	}
	nTreeNode* currentNode = session->getCurrentNode();
	return currentNode->getFilesRep() + std::string("\n");
}

int ServerOperations::connect(std::string pUser, std::string pSecKey, std::string pDisk){
	GeneralManager* manager = GeneralManager::getInstance();
	if (manager->getUser(pUser)->getSecurityKey() != pSecKey){
		return PS::NO_SESSION;
	}
	return manager->newSession(pUser, pDisk);
}

int ServerOperations::adduser(std::string pUser, std::string pSecKey, std::string pDisk){
	GeneralManager* manager = GeneralManager::getInstance();
	if (manager->getUser(pUser) != 0){
		std::cout<<"bad user"<<std::endl;
		return PS::NO_SESSION;
	}
	manager->addUser(pUser, pSecKey);
	return manager->newSession(pUser, pDisk);
}

std::string ServerOperations::openfile(int pSessionID, std::string pPath){
	GeneralManager* manager = GeneralManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	if (session == 0){
		return "*Error. Sesión no encontrada\n";
	}
	DiskGroup* diskgroup = session->getDiskGroup();
	nTreeNode* currentNode = session->getCurrentNode();

	std::string fileName = Tokenizer::dividePathAndName(pPath, &pPath);

	nTreeNode* cdNode = diskgroup->getNode(pPath, currentNode);
	if (cdNode == 0 || cdNode->getFile() == 0){
		return "?Error. Archivo inválido\n";
	}

	session->setCurrentNode(cdNode);
	session->setCurrentFormat( diskgroup->getRegFormat( cdNode->getFile() ) );
	session->setSeek(0);
	return "";
}

std::string ServerOperations::appendReg(int pSessionID, std::string pData){
	GeneralManager* manager = GeneralManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	if (session == 0){
		return "*Error. Sesión no encontrada\n";
	}
	DiskGroup* diskgroup = session->getDiskGroup();
	nTreeNode* currentNode = session->getCurrentNode();

	if (currentNode->getFile() == 0){
		return "?Error. No hay ningún archivo abierto\n";
	}

	RegisterSpace* format = diskgroup->getRegFormat(currentNode->getFile());
	DataNode* data = getData(pData, format);
	diskgroup->apendReg(data, currentNode->getFile());
	return "";

}

std::string ServerOperations::delReg(int pSessionID, int pRegNum){
	GeneralManager* manager = GeneralManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	if (session == 0){
		return "*Error. Sesión no encontrada\n";
	}
	DiskGroup* diskgroup = session->getDiskGroup();
	nTreeNode* currentNode = session->getCurrentNode();

	if (currentNode->getFile() == 0){
		return "?Error. No hay ningún archivo abierto\n";
	}	

	if (pRegNum == PS::SEEK_POS){
		pRegNum = session->getSeek();
	} else if (pRegNum > session->getCurrentNode()->getFile()->getRegCount()){
		return "?Error. El número de registro es inválido";
	}
	diskgroup->eraseReg(pRegNum, currentNode->getFile());
	return "";
}

std::string ServerOperations::write(int pSessionID, std::string pData, int pRegNum){
	GeneralManager* manager = GeneralManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	if (session == 0){
		return "*Error. Sesión no encontrada\n";
	}
	DiskGroup* diskgroup = session->getDiskGroup();
	nTreeNode* currentNode = session->getCurrentNode();

	if (currentNode->getFile() == 0){
		return "?Error. No hay ningún archivo abierto\n";
	}	

	if (pRegNum == PS::SEEK_POS){
		pRegNum = session->getSeek();
	} else if (pRegNum > session->getCurrentNode()->getFile()->getRegCount()){
		return "?Error. El número de registro es inválido";
	}

	RegisterSpace* format = diskgroup->getRegFormat(currentNode->getFile());
	DataNode* data = getData(pData, format);

	diskgroup->writeReg(pRegNum, data, currentNode->getFile());
	return "";
}

std::string ServerOperations::readReg(int pSessionID, int pRegNum){
	GeneralManager* manager = GeneralManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	if (session == 0){
		return "*Error. Sesión no encontrada\n";
	}
	DiskGroup* diskgroup = session->getDiskGroup();
	nTreeNode* currentNode = session->getCurrentNode();

	if (currentNode->getFile() == 0){
		return "?Error. No hay ningún archivo abierto\n";
	}	

	if (pRegNum == PS::SEEK_POS){
		pRegNum = session->getSeek();
	} else if (pRegNum > session->getCurrentNode()->getFile()->getRegCount()){
		return "?Error. El número de registro es inválido\n";
	}

	RegisterSpace* format = diskgroup->getRegFormat(currentNode->getFile());
	DataNode* data = diskgroup->readReg(pRegNum, currentNode->getFile());
	return toCSV(data, format);
}

std::string ServerOperations::close(int* pSessionID){
	if (*pSessionID == -1){
		return "See ya!\n";
	}
	GeneralManager* manager = GeneralManager::getInstance();
	Session* session = manager->getSession(*pSessionID);
	if (session == 0){
		return "*Error. Sesión no encontrada\n";
	}
	DiskGroup* diskgroup = session->getDiskGroup();
	nTreeNode* currentNode = session->getCurrentNode();
	if (currentNode->getFile() != 0){
		session->setCurrentNode(diskgroup->getNode("../", currentNode));
		session->setSeek(0);
		return "";
	} else {
		std::string user = session->getUser();
		manager->closeSession(*pSessionID);
		*pSessionID = -1;
		return "See ya, " + user + ".\n";
	}
}

std::string ServerOperations::getInfo(int pSessionID){
	GeneralManager* manager = GeneralManager::getInstance();
	Session* session = manager->getSession(pSessionID);
	if (session == 0){
		return "*Error. Sesión no encontrada\n";
	}
	return session->getCurrentNode()->getTotalPath() + " " + session->getUser();
}
