#include "noraid.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 		PRIVATE		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void NoRaid::eraseFile(iFile* pFile)
{
	
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 		PUBLIC		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

NoRaid::NoRaid(std::string pID, int pBlockSize)
{

}

NoRaid::NoRaid(std::string pID, int pBlockSize, int pMaxSize, bool pFunctional, bool pWorking)
{

}

/* operaciones sobre el arbol n-ario */

DataNode * NoRaid::getFile(iFile* pFile)
{
	
}

void NoRaid::startDiskGroup()
{

}
	
void NoRaid::stopDiskGroup()
{

}

void NoRaid::deleteFile(nTreeNode* pNode)
{
	iFile * temporal = pNode->getFile();
	temporal->~iFile;
	_files->erase(pNode);
}

nTreeNode * NoRaid::createFile(nTreeNode* pNode, std::string pName, RegisterBuffer* pRegister, std::string pUser)
{
	iFile * temporal = new iFile(pName, 0, _blockSize, 0);
	temporal->createFile(pRegister);
	_files->insert(temporal, pNode, pName, pUser, "");
}

/* operaciones sobre el registros */

short NoRaid::apendReg(DataNode* pData, iFile* pFile)
{

}

short NoRaid::writeReg(int pRegisterNumber, DataNode* pData, iFile* pFile)
{

}

DataBuffer* NoRaid::readReg(int pRegisterNumber, iFile* pFile)
{

}

void NoRaid::eraseReg(int pRegisterNumber, iFile* pFile)
{

}

RegisterBuffer* NoRaid::getRegFormat(iFile* pFile)
{

}

/* operaciones administrativas */

void NoRaid::format()
{
	
}

/* operaciones sobre discos */

std::string NoRaid::toBinario(DataNode* pData)
{
	
}
