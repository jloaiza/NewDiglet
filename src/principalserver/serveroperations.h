#ifndef SERVEROPERATIONS
#define SERVEROPERATIONS

#include <string>
#include "datanode.h"
#include "registerspace.h"

class ServerOperations{
private:

	/**
	* Convert data to CSV.
	*
	* @param pData Nodes that conteins the information
	* @param pFormat Format of the information
	**/
	static std::string toCSV(DataNode* pData, RegisterSpace* pFormat);

	/**
	* Gets the register-format representation needed by the program from an entry message
	*
	* @param pFormat string with format description
	* @return RegisterSpace. A kind of list node that conteins the format information
	**/
	static RegisterSpace* getFormat(std::string pFormat);

	/**
	* Gets the data representation need by the program from a message.
	*
	* @param pData string that conteins the data
	* @param pFormat register-format to set the data
	**/
	static DataNode* getData(std::string pData, RegisterSpace* pFormat);

public:
	
	static std::string get(int pSessionID, std::string pPath);

	static std::string cd(int pSessionID, std::string pPath);
	static std::string rm(int pSessionID, std::string pPath);
	static std::string moveSeek(int pSessionID, int pSeekPos);
	static std::string mkdir(int pSessionID, std::string pName);
	static std::string touch(int pSessionID, std::string pPath, std::string pFormat);
	static int connect(std::string pUser, std::string pSecKey, std::string pDisk);
	static int adduser(std::string pUser, std::string pSecKey, std::string pDisk);
	static std::string openfile(int pSessionID, std::string pPath);
	static std::string appendReg(int pSessionID, std::string pData);
	static std::string delReg(int pSessionID, int pRegNum);
	static std::string write(int pSessionID, std::string pData, int pRegNum);
	static std::string readReg(int pSessionID, int pRegNum);
	static std::string close(int* pSessionID);
	static std::string getInfo(int pSessionID);

};


#endif /* SERVEROPERATIONS */