#include "raidzero.h"

RaidZero::RaidZero(std::string pID, int pBlockSize){
	
}

RaidZero::RaidZero(std::string pID, int pBlockSize, int pMaxSize, bool pFunctional, bool pWorking){
	
}


void RaidZero::startDiskGroup(){

}
	
void RaidZero::stopDiskGroup(){

}


DataNode* RaidZero::getFile(iFile* pFile){

}

void RaidZero::deleteFile(nTreeNode* pNode){

}

nTreeNode* RaidZero::createFile(nTreeNode* pActual, std::string pName, RegisterSpace* pRegister, std::string pUser){

}

short RaidZero::apendReg(DataNode* pData, iFile* pFile){

}

short RaidZero::writeReg(int pRegisterNumber, DataNode* pData, iFile* pFile){

}

DataNode* RaidZero::readReg(int pRegisterNumber, iFile* pFile){

}

void RaidZero::eraseReg(int pRegisterNumber, iFile* pFile){

}

RegisterSpace* RaidZero::getRegFormat(iFile* pFile){

}

void RaidZero::format(){

}

std::string RaidZero::toBinario(DataNode* pData){

}

void RaidZero::eraseFile(iFile* pFile){

}