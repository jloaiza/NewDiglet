#ifndef RAIDONE
#define RAIDONE

#include "diskgroup.h"
#include "../structures/doublelinkedlist/listnode.h"

class RaidOne : public DiskGroup{
public:

	RaidOne(std::string pID, int pBlockSize);
	RaidOne(std::string pID, int pBlockSize, int pMaxSize, bool pFunctional, bool pWorking);

	void startDiskGroup();
	
	void stopDiskGroup();
	
	DataNode* getFile(iFile* pFile);

	ListNode<Disk>* getNextDisk(ListNode<Disk>* pActual);

	void deleteFile(nTreeNode* pNode);

	nTreeNode* createFile(nTreeNode* pActual, std::string pName, RegisterSpace* pRegister, std::string pUser);	

	short apendReg(DataNode* pData, iFile* pFile);

	short writeReg(int pRegisterNumber, DataNode* pData, iFile* pFile);

	DataNode* readReg(int pRegisterNumber, iFile* pFile);

	void eraseReg(int pRegisterNumber, iFile* pFile);

	RegisterSpace* getRegFormat(iFile* pFile);

	void format();

private:

	static const int FILENAME_SIZE = 75;
	static const int AUTHOR_SIZE = 25;
	static const int FDATA_SIZE = 4;
	static const int REGS_SIZE = 2;
	static const int REGISTER_SIZE = 27;
	static const int REGCOL_SIZE = 25;
	static const int REGTYPE_SIZE = 1;
	static const int REGCOLSIZE_SIZE = 1;
	static const int BLOCKNEXT_SIZE = 10;

	ListNode<Disk>* _currentDisk;

	void eraseFile(iFile* pFile);

};

#endif /* RAIDONE */