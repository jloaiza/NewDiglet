#ifndef NORAID
#define NORAID

#include "diskgroup.h"

class NoRaid : public DiskGroup
{

private:

	void eraseFile(iFile* pFile);
	SimpleList* Register2binary (RegisterSpace* pRegister, short pMetadataNumber, SimpleList* pBloques);

public:

	NoRaid(std::string pID, int pBlockSize);
	NoRaid(std::string pID, int pBlockSize, int pMaxSize, bool pFunctional, bool pWorking);

	/* operaciones sobre el arbol n-ario */

	DataNode * getFile(iFile* pFile);
	void startDiskGroup();
	void stopDiskGroup();
	void deleteFile(nTreeNode* pNode);
	nTreeNode * createFile(nTreeNode* pNode,  std::string pName, RegisterSpace* pRegister, std::string pUser);

	/* operaciones sobre el registros */

	short apendReg(DataNode* pData, iFile* pFile);
	short writeReg(int pRegisterNumber, DataNode* pData, iFile* pFile);
	DataNode* readReg(int pRegisterNumber, iFile* pFile);
	void eraseReg(int pRegisterNumber, iFile* pFile);
	RegisterSpace* getRegFormat(iFile* pFile);

	/* operaciones administrativas */

	void format();

	/* operaciones sobre discos */

	std::string toBinario(DataNode* pData);

};

#endif /* NORAID */
