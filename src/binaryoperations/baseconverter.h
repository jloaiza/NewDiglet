#ifndef BASECONVERTER
#define BASECONVERTER

#include <string>

class BaseConverter{

public:

	static std::string unum2bin(unsigned long pNumber, int pSize);
	static std::string snum2bin(long pNumber, int pSize);
	static std::string double2bin(double pNumber);

	static unsigned long to_ulong(std::string pBinary);
	static long to_slong(std::string pBinary);
	static double toDouble(std::string pBinary);
	static std::string multChar(char pChar, int pCount);

private:

	static std::string complement(std::string pBits);
	static std::string decimals2bin(double pNumber);
	static double decimalsBin2double(std::string pBits);

};


#endif /* BASECONVERTER */