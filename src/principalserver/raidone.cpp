#include "raidone.h"

RaidOne::RaidOne(std::string pID, int pBlockSize){
	
}

RaidOne::RaidOne(std::string pID, int pBlockSize, int pMaxSize, bool pFunctional, bool pWorking){

}

void RaidOne::startDiskGroup(){

}
	
void RaidOne::stopDiskGroup(){

}

DataNode* RaidOne::getFile(iFile* pFile){

}

void RaidOne::deleteFile(nTreeNode* pNode){

}

nTreeNode* RaidOne::createFile(nTreeNode* pActual, std::string pName, RegisterSpace* pRegister, std::string pUser){

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

}

std::string RaidOne::toBinario(DataNode* pData){

}

void RaidOne::eraseFile(iFile* pFile){

}