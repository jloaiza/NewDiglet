#include "raidone.h"
#include "databuffer.h"
#include "../include/constants.h"
#include "../binaryoperations/byteshandler.h"
#include "../tokenizer/tokenizer.h"
#include <iostream>

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
	_currentDisk = _diskList->getHead();
}

void RaidOne::startDiskGroup(){
	if (_functional){
		_working = true;
	}
}
	
void RaidOne::stopDiskGroup(){
	_working = false;
}

DataNode* RaidOne::getFile(iFile* pFile){

}

void RaidOne::deleteFile(nTreeNode* pNode){

}

nTreeNode* RaidOne::createFile(nTreeNode* pActual, std::string pName, RegisterSpace* pRegister, std::string pUser){
	std::cout<<"createFile"<<std::endl;
	DataBuffer header = DataBuffer(); //Almacenará la información del header

	std::cout<<"cf0"<<std::endl;
	//Tomar la información
	int dataBlock = 0;
	short formatSize = pRegister->totalLength()*REGISTER_SIZE;

	std::cout<<"cf1"<<std::endl;
	//Agregar la informacion a los dataspaces
	header.addToBuffer(&pName, STRING, FILENAME_SIZE);
	header.addToBuffer(&pUser, STRING, AUTHOR_SIZE);
	header.addToBuffer(&dataBlock, INT, FDATA_SIZE);
	header.addToBuffer(&formatSize, SHORT, REGS_SIZE);

	std::cout<<"cf2"<<std::endl;
	//Cargar una representacion del register format como data nodes
	DataNode* regData = toDataNode(pRegister, REGCOL_SIZE, REGTYPE_SIZE, REGCOLSIZE_SIZE);

	//head va ser el string binario con todos los datos
	std::string head = toBinary(header.getBuffer());
	head += toBinary(regData);

	std::cout<<"cf3"<<std::endl;
	//Se divide el head en los espacios necesarios descontando el espacio ocupado por los siguientes bloques
	ListNode<std::string>* strips = getStrips(head, _blockSize-BLOCKNEXT_SIZE);

	std::cout<<"cf4"<<std::endl;
	//blocks contendrá los bloques donde son incertados los datos
	DoubleLinkedList<int, void> blocks = DoubleLinkedList<int, void>();

	ListNode<Disk>* tempStart = _currentDisk; //Copia del disco antes de empezar inserción

	//Insercion:
	while(strips != 0){
		if (!_currentDisk->getData()->isAlive()){
			std::cout<<"?Error. Se ha perdido la conexión con el disco: "<<_currentDisk->getData()->getDiskDirection()<<"."<<std::endl;
			std::cout<<"El diskgroup: "<<_id<<" estará deshabilitado hasta que se repare el error."<<std::endl;
			_working = false;
			_functional = false;
			return 0;
		}
		std::string toWrite = BytesHandler::bin2str(*strips->getData());
		std::cout<<"cf4.1"<<std::endl;
		int* ins = new int(_currentDisk->getData()->writeBlock(toWrite));
		std::cout<<"cf4.1.2"<<std::endl;
		if (*ins == 0){
			std::cout<<"?Error. No se pudo escribir en uno de los discos, la escritura será interrumpida."<<std::endl;
			std::cout<<"El archivo estaŕa corrupto."<<std::endl;
			std::cout<<"El diskgroup: '"<<_id<<"' estará deshabilitado hasta que se repare el error."<<std::endl;
			_working = false;
			_functional = false;
			return 0;
		}
		std::cout<<"cf4.1.3"<<std::endl;
		blocks.insertEnd(ins);
		std::cout<<"write block: "<<*ins<<std::endl;
		std::cout<<"cf4.2"<<std::endl;
		strips = strips->getNext();

		_currentDisk = getNextDisk(_currentDisk);
	}

	//Se crea el archivo para el árbol
	std::cout<<"cf5"<<std::endl;
	iFile* file = new iFile(tempStart->getData()->getDiskDirection(), -1);
	ListNode<int>* iBlock = blocks.getHead();
	file->setStartBlock( *iBlock->getData() );

	std::cout<<"cf6"<<std::endl;
	//Se setean los bloques siguientes donde hubieron inserciones
	while (iBlock->getNext() != 0){
		int ip1, ip2, ip3, ip4;
		short disk;

		std::cout<<"cf6.1"<<std::endl;
		ip1 = std::stoi(Tokenizer::getCommandSpace(getNextDisk(tempStart)->getData()->getIp(), 1, '.'));
		ip2 = std::stoi(Tokenizer::getCommandSpace(getNextDisk(tempStart)->getData()->getIp(), 2, '.'));
		ip3 = std::stoi(Tokenizer::getCommandSpace(getNextDisk(tempStart)->getData()->getIp(), 3, '.'));
		ip4 = std::stoi(Tokenizer::getCommandSpace(getNextDisk(tempStart)->getData()->getIp(), 4, '.'));
		disk = tempStart->getNext()->getData()->getDiskID();
		
		int nextBlock = *iBlock->getNext()->getData();

		std::cout<<"cf6.2"<<std::endl;
		std::string nextDir = "";
		nextDir += BytesHandler::unum2bin(ip1, 1);
		nextDir += BytesHandler::unum2bin(ip2, 1);
		nextDir += BytesHandler::unum2bin(ip3, 1);
		nextDir += BytesHandler::unum2bin(ip4, 1);
		nextDir += BytesHandler::unum2bin(disk, 2);
		nextDir += BytesHandler::unum2bin(nextBlock, 4);
		nextDir = BytesHandler::bin2str(nextDir);

		std::cout<<"cf6.3"<<std::endl;
		tempStart->getData()->writeBytes(*iBlock->getData(), _blockSize-BLOCKNEXT_SIZE, BLOCKNEXT_SIZE, nextDir);
		std::cout<<"cf6.4"<<std::endl;
		iBlock = iBlock->getNext();
		std::cout<<"cf6.5"<<std::endl;
	}
	std::cout<<"cf7"<<std::endl;
	//Se incerta el ifile en el árbol y se devuelve el nodo correspondiente
	_files->insert(file, pActual, pName, pUser, "");
	return _files->getNode(pActual, pName);
}

ListNode<Disk>* RaidOne::getNextDisk(ListNode<Disk>* pActual){
	if (pActual->getNext() == 0){
		return _diskList->getHead();
	} else {
		return pActual->getNext();
	}
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
	_functional = true;
	ListNode<Disk>* iNode = _diskList->getHead();
	while(iNode != 0){
		iNode->getData()->format(_blockSize);
		iNode = iNode->getNext();
	}
	_currentDisk = _diskList->getHead();
}

void RaidOne::eraseFile(iFile* pFile){

}