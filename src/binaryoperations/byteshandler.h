#ifndef BYTESHANDLER
#define BYTESHANDLER

#include <string>
#include "baseconverter.h"

class BytesHandler : public BaseConverter
{
public:

	static std::string unum2bin(unsigned long pNum, int pSize);
	static std::string snum2bin(long pNum, int pSize);
	static std::string string2bin(std::string pString, int pSize);
	static std::string bin2str(std::string pBinary);
	
};


#endif /* BYTESHANDLER */