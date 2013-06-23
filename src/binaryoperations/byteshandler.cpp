#include "byteshandler.h"

#include <iostream>

std::string BytesHandler::unum2bin(unsigned long pNum, int pSize){
	return BaseConverter::unum2bin(pNum, pSize*8);
}

std::string BytesHandler::snum2bin(long pNum, int pSize){
	return BaseConverter::snum2bin(pNum, pSize*8);
}

std::string BytesHandler::string2bin(std::string pString, int pSize){

	std::string buffer;
	pString += BaseConverter::multChar(0, pSize*8 - pString.length()*8);

	for (int i = 0; i < pString.length(); i++){
		buffer += BaseConverter::unum2bin(pString[i], 8);
	}

	return buffer;
}

std::string BytesHandler::bin2str(std::string pBinary){
	
	std::string buffer;
	char ichar;

	for (int i = 0; i + 8 <= pBinary.length(); i += 8){
		ichar = BaseConverter::to_ulong(pBinary.substr(i, 8));
		buffer += ichar;
	}

	return buffer;
}

