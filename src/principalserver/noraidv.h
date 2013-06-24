#ifndef NORAID
#define NORAID

class RegisterSpace;
class nTreeNode;
class nTree;

class NoRaid : public DiskGroup
{
private:

	short _ID;
	int _BlockSize, _NumDisks;
	DataBuffer* _outBuffer;
	bool _Functional, _Working
	SimpleList * _diskList;

	void eraseFile(iFile* pFile);

public:

	/* operaciones sobre el arbol n-ario */

	DataNode * getFile(iFile pFile);
	void deleteFile(nTreeNode* pNode);
	nTreeNode * createFile(std::string pName, pRegisterList pRegister, std::string pUser);
	nTreeNode* getNode(std::string pRelativePath, nTreeNode* pNode);

	/* operaciones sobre el registros */

	short apendReg(DataNode* pData, iFile* pFile);
	short writeReg(int pRegisterNumber, DataNode* pData, iFile* pFile);
	DataNode* readReg(int pRegisterNumber, iFile* pFile);
	void eraseReg(int pRegisterNumber, iFile* pFile);
	RegisterSpace* getRegFormat(iFile* pFile);

	/* operaciones administrativas */

	format();
	std::string getID();
	int getBlockSize();
	bool isWorking();
	bool isFunctional();

	/* operaciones sobre discos */

	SimpleList* getDiskList();
	void addDisk(Disk* pDisk);
	void removeDisk(std::string pIP, std::string pID);
	void setBlockSize(int pSize);
	std::string toBinario(DataNode* pData);

};

#endif
