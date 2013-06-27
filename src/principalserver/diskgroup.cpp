#include "diskgroup.h"
#include "../binaryoperations/byteshandler.h"
#include "../include/constants.h"
#include "databuffer.h"

bool DiskGroup::operator==(std::string& pID){
	return _id == pID;
}

bool DiskGroup::operator>(std::string& pID){
	return _id > pID;
}

bool DiskGroup::operator>=(std::string& pID){
	return _id >= pID;
}

bool DiskGroup::operator<(std::string& pID){
	return _id < pID;
}

bool DiskGroup::operator<=(std::string& pID){
	return _id <= pID;
}

bool DiskGroup::operator!=(std::string& pID){
	return _id != pID;
}

bool DiskGroup::operator==(DiskGroup& pDiskGroup){
	return _id == pDiskGroup.getID();
}

bool DiskGroup::operator>(DiskGroup& pDiskGroup){
	return _id > pDiskGroup.getID();
}
bool DiskGroup::operator>=(DiskGroup& pDiskGroup){
	return _id >= pDiskGroup.getID();
}

bool DiskGroup::operator<(DiskGroup& pDiskGroup){
	return _id < pDiskGroup.getID();
}

bool DiskGroup::operator<=(DiskGroup& pDiskGroup){
	return _id <= pDiskGroup.getID();
}

bool DiskGroup::operator!=(DiskGroup& pDiskGroup){
	return _id != pDiskGroup.getID();
}

std::string DiskGroup::getDiskList(){
	ListNode<Disk>* aux = _diskList->getHead();
	std::string message;
	message += std::string("List of diskroup ") + _id + std::string(" order of list:\nDISK NAME  & CONECTION STATUS") + "\n";
	while (aux != 0){
		message += aux->getData()->getDiskDirection() + "  ";
		message += (aux->getData()->isAlive()?"online":"offline") + '\n';
		aux = aux->getNext();
	}
	return message;
}

nTreeNode* DiskGroup::getNode(std::string pRelativePath, nTreeNode* pCurrentNode){
	return _files->getNode(pCurrentNode, pRelativePath);
}

nTreeNode* DiskGroup::getRoot(){
	return _files->getRoot();
}

void DiskGroup::createDir(nTreeNode* pFolderNode, std::string pName, std::string pUser){
	_files->insert(0, pFolderNode, pName, pUser, "");
}

void DiskGroup::addDisk(Disk* pDisk){
	_diskList->insertEnd(pDisk);
}

void DiskGroup::removeDisk(std::string pIP, short pDiskID){
	std::string* direction = new std::string(pIP + std::string(":") + std::to_string(pDiskID));
	_diskList->erase(direction);
	delete direction;
}

void DiskGroup::loadTree(std::string pTreePath){
	
}

std::string DiskGroup::toBinary(DataNode* pData){
	DataNode* iNode = pData;
	std::string bin = "";

	while (iNode != 0){
		if (iNode->getType() == STRING){
			bin += BytesHandler::string2bin(*(std::string*)(iNode->getData()) , iNode->getSize() );
		} else if (iNode->getType() == DOUBLE){
			bin += BytesHandler::double2bin(*(double*)(iNode->getData()));
		} else {
			bin += BytesHandler::snum2bin( *(long*)(iNode->getData()) , iNode->getSize() );
		}
		iNode = iNode->getNext();
	}

	return bin;
}

DataNode* DiskGroup::toDataNode(RegisterSpace* pRegister, int pColNameSize, int pTypeSize, int pDataSize){
	RegisterSpace* iSpace = pRegister;
	DataBuffer* data = new DataBuffer();
	while (iSpace != 0){
		data->addToBuffer((new char(iSpace->getType())), CHAR, pTypeSize);
		data->addToBuffer((new char(iSpace->getSize())), CHAR, pDataSize);
		data->addToBuffer((new std::string(iSpace->getName())), STRING, pColNameSize);
		iSpace = iSpace->getNext();
	}
	return data->getBuffer();
}

ListNode<std::string>* DiskGroup::getStrips(std::string pMessage, int pBlockSize){
	DoubleLinkedList<std::string, std::string>* strips = new DoubleLinkedList<std::string, std::string>();
	std::string msg = pMessage;
	bool stripping = true;
	while (stripping){
		std::string* strip = new std::string(msg.substr(0, pBlockSize));
		strips->insertEnd(strip);
		if (msg.length()<=pBlockSize){
			stripping = false;
		} else {
			msg = msg.substr(pBlockSize, 2*pBlockSize);
		}
	}
	return strips->getHead();
}