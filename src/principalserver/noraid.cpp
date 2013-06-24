#include "noraid.h"

NoRaid::NoRaid(std::string pID, int pBlockSize){

}

NoRaid::NoRaid(std::string pID, int pBlockSize, int pMaxSize, bool pFunctional, bool pWorking){

}

void NoRaid::startDiskGroup(){

}
	
void NoRaid::stopDiskGroup(){

}

DataNode* NoRaid::getFile(iFile* pFile){

}

void NoRaid::deleteFile(nTreeNode* pNode){

}

nTreeNode* NoRaid::createFile(nTreeNode* pActual, std::string pName, RegisterSpace* pRegister, std::string pUser){

}

short NoRaid::apendReg(DataNode* pData, iFile* pFile){

}

short NoRaid::writeReg(int pRegisterNumber, DataNode* pData, iFile* pFile){

}

DataNode* NoRaid::readReg(int pRegisterNumber, iFile* pFile){

}

void NoRaid::eraseReg(int pRegisterNumber, iFile* pFile){

}

RegisterSpace* NoRaid::getRegFormat(iFile* pFile){

}

void NoRaid::format(){

}

std::string NoRaid::toBinario(DataNode* pData){

}

void NoRaid::eraseFile(iFile* pFile){

}