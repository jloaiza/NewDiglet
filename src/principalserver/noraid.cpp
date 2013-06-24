#include "diskgroup.h"
#include "noraid.h"
#include "../structures/ntreenode.h"
#include "../structures/nTree.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 		PRIVATE		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void NoRaid::eraseFile(iFile* pFile)
{
	
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 		PUBLIC		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* operaciones sobre el arbol n-ario */

DataNode * NoRaid::getFile(iFile* pFile)
{
	RegisterBuffer * temporal = pFile->getFileMetadata();
	return pFile->getFileData(temporal);
}

void NoRaid::deleteFile(nTreeNode* pNode)
{
	iFile * temporal = pNode->getFile();
	temporal->~iFile;
	_tree->erase(pNode);
}

nTreeNode * NoRaid::createFile(nTreeNode* pNode, std::string pName, RegisterSpace* pRegister, std::string pUser)
{
	iFile * temporal = new iFile(pName, 0, _BlockSize, 0);
	temporal->createFile(pRegister);
	_tree->insert(temporal, pNode, pName, pUser, "");
}

nTreeNode* NoRaid::getNode(std::string pRelativePath, nTreeNode* pNode)
{
	_tree->erase(pNode, pRelativePath);
}

/* operaciones sobre el registros */

short NoRaid::apendReg(DataNode* pData, iFile* pFile)
{
	return iFile->apendReg(pData);
}

short NoRaid::writeReg(int pRegisterNumber, DataNode* pData, iFile* pFile)
{
	return pFile->writeReg(pRegisterNumber, pData);
}

DataNode* NoRaid::readReg(int pRegisterNumber, iFile* pFile)
{
	return pFile->readReg(pRegisterNumber);
}

void NoRaid::eraseReg(int pRegisterNumber, iFile* pFile)
{
	pFile->eraseReg(pRegisterNumber);
}

RegisterSpace* NoRaid::getRegFormat(iFile* pFile)
{
	return pFile->getFileMetadata();
}

/* operaciones administrativas */

void NoRaid::format()
{
	
}

/* operaciones sobre discos */

DoubleLinkedList<Disk, std::string>* NoRaid::getDiskList()
{
	return _diskList;
}

void NoRaid::addDisk(Disk* pDisk)
{
	_diskList->insertStart(pDisk); 
}

void NoRaid::removeDisk(std::string pIP, std::string pID)
{
	_diskList->erase(
}

void NoRaid::setBlockSize(int pSize);

std::string NoRaid::toBinario(DataNode* pData);
