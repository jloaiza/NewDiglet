#include "raidfive.h"

RaidFive::RaidFive(std::string pID, int pBlockSize){

}

RaidFive::RaidFive(std::string pID, int pBlockSize, int pMaxSize, bool pFunctional, bool pWorking){
	
}

void RaidFive::startDiskGroup(){

}
	
void RaidFive::stopDiskGroup(){

}

DataNode* RaidFive::getFile(iFile* pFile){

}

void RaidFive::deleteFile(nTreeNode* pNode){

}

nTreeNode* RaidFive::createFile(nTreeNode* pActual, std::string pName, RegisterSpace* pRegister, std::string pUser){

}

short RaidFive::apendReg(DataNode* pData, iFile* pFile){

}

short RaidFive::writeReg(int pRegisterNumber, DataNode* pData, iFile* pFile){

}

DataNode* RaidFive::readReg(int pRegisterNumber, iFile* pFile){

}

void RaidFive::eraseReg(int pRegisterNumber, iFile* pFile){

}

RegisterSpace* RaidFive::getRegFormat(iFile* pFile){

}

void RaidFive::format(){

}

std::string RaidFive::toBinario(DataNode* pData){

}

void RaidFive::eraseFile(iFile* pFile){

}