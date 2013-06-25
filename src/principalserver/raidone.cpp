#include "raidone.h"
#include "databuffer.h"
#include "../include/constants.h"
#include "../binaryoperations/byteshandler.h"
#include "../tokenizer/tokenizer.h"

RaidOne::RaidOne(std::string pID, int pBlockSize){
	_id = pID;
	_maxSize = 0;
	_blockSize = pBlockSize;
	_raid = 1;
	_working = false;
	_functional = false;
	_files = new nTree(); //Sustituir más adelante por loadTree
	_diskList = new DoubleLinkedList<Disk, std::string>();
	_currentDisk = _diskList->getHead();
}

RaidOne::RaidOne(std::string pID, int pBlockSize, int pMaxSize, bool pFunctional, bool pWorking){
	_id = pID;
	_blockSize = pBlockSize;
	_maxSize = pMaxSize;
	_functional = pFunctional;
	_working = pWorking;
	_files = new nTree(); //Sustituir más adelante por loadTree
}

void RaidOne::startDiskGroup(){
	if (_working){
		_functional = true;
	}
}
	
void RaidOne::stopDiskGroup(){
	_functional = false;
}

DataNode* RaidOne::getFile(iFile* pFile){

}

void RaidOne::deleteFile(nTreeNode* pNode){

}

nTreeNode* RaidOne::createFile(nTreeNode* pActual, std::string pName, RegisterSpace* pRegister, std::string pUser){
	DataBuffer header = DataBuffer(); //Almacenará la información del header

	//Tomar la información
	std::string* name = new std::string(pName);
	std::string* author = new std::string(pUser);
	int* dataBlock = new int(0);
	short* formatSize = new short(pRegister->totalLength()*REGISTER_SIZE);

	//Agregar la informacion a los dataspaces
	header.addToBuffer(name, STRING, FILENAME_SIZE);
	header.addToBuffer(author, STRING, AUTHOR_SIZE);
	header.addToBuffer(dataBlock, INT, FDATA_SIZE);
	header.addToBuffer(formatSize, SHORT, REGS_SIZE);

	//Cargar una representacion del register format como data nodes
	DataNode* regData = toDataNode(pRegister, REGCOL_SIZE, REGTYPE_SIZE, REGCOLSIZE_SIZE);

	//head va ser el string binario con todos los datos
	std::string head = toBinary(header.getBuffer());
	head += toBinary(regData);

	//Se divide el head en los espacios necesarios descontando el espacio ocupado por los siguientes bloques
	ListNode<std::string>* strips = getStrips(head, _blockSize-BLOCKNEXT_SIZE);

	//blocks contendrá los bloques donde son incertados los datos
	DoubleLinkedList<int, void> blocks = DoubleLinkedList<int, void>();

	ListNode<Disk>* tempStart = _currentDisk; //Copia del disco antes de empezar inserción

	//Insercion:
	while(strips != 0){

		std::string toWrite = BytesHandler::bin2str(*strips->getData());
		blocks.insertEnd(new int(_currentDisk->getData()->writeBlock(toWrite)));

		strips = strips->getNext();

		if (_currentDisk->getNext() != 0){
			_currentDisk = _currentDisk->getNext();
		} else {
			_currentDisk = _diskList->getHead();
		}
	}

	//Se crea el archivo para el árbol
	iFile* file = new iFile(tempStart->getData()->getDiskDirection(), -1);
	ListNode<int>* iBlock = blocks.getHead();
	file->setStartBlock( *iBlock->getData() );

	//Se setean los bloques siguientes donde hubieron inserciones
	while (iBlock->getNext() != 0){
		int ip1, ip2, ip3, ip4;
		short disk;
		if (tempStart->getNext() == 0){
			ip1 = std::stoi(Tokenizer::getCommandSpace(_diskList->getHead()->getData()->getDiskDirection(), 1, ':'));
			ip2 = std::stoi(Tokenizer::getCommandSpace(_diskList->getHead()->getData()->getDiskDirection(), 2, ':'));
			ip3 = std::stoi(Tokenizer::getCommandSpace(_diskList->getHead()->getData()->getDiskDirection(), 3, ':'));
			ip4 = std::stoi(Tokenizer::getCommandSpace(_diskList->getHead()->getData()->getDiskDirection(), 4, ':'));
			disk = _diskList->getHead()->getData()->getDiskID();

		} else {
			ip1 = std::stoi(Tokenizer::getCommandSpace(tempStart->getNext()->getData()->getDiskDirection(), 1, ':'));
			ip2 = std::stoi(Tokenizer::getCommandSpace(tempStart->getNext()->getData()->getDiskDirection(), 2, ':'));
			ip3 = std::stoi(Tokenizer::getCommandSpace(tempStart->getNext()->getData()->getDiskDirection(), 3, ':'));
			ip4 = std::stoi(Tokenizer::getCommandSpace(tempStart->getNext()->getData()->getDiskDirection(), 4, ':'));
			disk = tempStart->getNext()->getData()->getDiskID();
		}

		int nextBlock = *iBlock->getNext()->getData();

		std::string nextDir = "";
		nextDir += BytesHandler::unum2bin(ip1, 1);
		nextDir += BytesHandler::unum2bin(ip2, 1);
		nextDir += BytesHandler::unum2bin(ip3, 1);
		nextDir += BytesHandler::unum2bin(ip4, 1);
		nextDir += BytesHandler::unum2bin(disk, 2);
		nextDir += BytesHandler::unum2bin(nextBlock, 4);
		nextDir = BytesHandler::bin2str(nextDir);

		tempStart->getData()->writeBytes(*iBlock->getData(), _blockSize-BLOCKNEXT_SIZE, BLOCKNEXT_SIZE, nextDir);
	}

	//Se incerta el ifile en el árbol y se devuelve el nodo correspondiente
	_files->insert(file, pActual, pName, pUser, "");
	return _files->getNode(pActual, pName);
}

short RaidOne::apendReg(DataNode* pData, iFile* pFile){	

}

short RaidOne::writeReg(int pRegisterNumber, DataNode* pData, iFile* pFile){

}

DataNode* RaidOne::readReg(int pRegisterNumber, iFile* pFile){

}

void RaidOne::eraseReg(int pRegisterNumber, iFile* pFile){

}

RegisterSpace* RaidOne::getRegFormat(iFile* pFile){

}

void RaidOne::format(){

}

void RaidOne::eraseFile(iFile* pFile){

}