#include "diskgroup.h"
#include "noraid.h"
#include "../structures/ntreenode.h"
#include "../structures/nTree.h"

void NoRaid::eraseFile(iFile* pFile);

/* operaciones sobre el arbol n-ario */

DataNode * NoRaid::getFile(iFile pFile);

void NoRaid::deleteFile(nTreeNode* pNode);

nTreeNode * NoRaid::createFile(std::string pName, pRegisterList pRegister, std::string pUser);

nTreeNode* NoRaid::getNode(std::string pRelativePath, nTreeNode* pNode);

/* operaciones sobre el registros */

short NoRaid::apendReg(DataNode* pData, iFile* pFile)
{
	iFile->apendReg(pData);	////// agregar metodo al iFile
}

short NoRaid::writeReg(int pRegisterNumber, DataNode* pData, iFile* pFile);

DataNode* NoRaid::readReg(int pRegisterNumber, iFile* pFile);

void NoRaid::eraseReg(int pRegisterNumber, iFile* pFile);

RegisterSpace* NoRaid::getRegFormat(iFile* pFile);

/* operaciones administrativas */

void NoRaid::format();

std::string NoRaid::getID();

int NoRaid::getBlockSize();

bool NoRaid::isWorking();

bool NoRaid::isFunctional();

/* operaciones sobre discos */

SimpleList* NoRaid::getDiskList();

void NoRaid::addDisk(Disk* pDisk);

void NoRaid::removeDisk(std::string pIP, std::string pID);

void NoRaid::setBlockSize(int pSize);

std::string NoRaid::toBinario(DataNode* pData);
