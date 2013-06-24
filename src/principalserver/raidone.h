#ifndef RAIDONE
#define RAIDONE

#include "diskgroup.h"

class RaidOne : public DiskGroup{
public:

	RaidOne(std::string pID, int pBlockSize);
	RaidOne(std::string pID, int pBlockSize, int pMaxSize, bool pFunctional, bool pWorking);

	void startDiskGroup();
	
	void stopDiskGroup();
	
	DataNode* getFile(iFile* pFile);

	void deleteFile(nTreeNode* pNode);

	nTreeNode* createFile(nTreeNode* pActual, std::string pName, RegisterSpace* pRegister, std::string pUser);	

	short apendReg(DataNode* pData, iFile* pFile);

	short writeReg(int pRegisterNumber, DataNode* pData, iFile* pFile);

	DataNode* readReg(int pRegisterNumber, iFile* pFile);

	void eraseReg(int pRegisterNumber, iFile* pFile);

	RegisterSpace* getRegFormat(iFile* pFile);

	void format();

	std::string toBinario(DataNode* pData);

private:
	
	void eraseFile(iFile* pFile);


};

#endif /* RAIDONE */