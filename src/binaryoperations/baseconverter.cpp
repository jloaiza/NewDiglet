#include "baseconverter.h"
#include <cstdlib>
#include <cmath>

#include <iostream>

std::string BaseConverter::unum2bin(unsigned long pNumber, int pSize){
	std::string buffer;
	bool onConv = true;

	while (onConv){
		buffer = std::to_string(pNumber%2) + buffer;
		pNumber /= 2;
		if (pNumber == 0){
			onConv = false;
		}
	}

	if (pSize <= 0){
		return buffer;
	} else if (pSize <= buffer.length()){
		return buffer.substr(buffer.length() - pSize, pSize);
	} else {
		return multChar('0', pSize-buffer.length() ) + buffer;
	}
}

std::string BaseConverter::snum2bin(long pNumber, int pSize){
	std::string numBin = unum2bin(abs(pNumber), pSize);
	if (pNumber < 0){
		numBin = complement(numBin);
	}
	return numBin;
}

std::string BaseConverter::double2bin(double pNumber){
	std::string buffer;

	//Signo
	buffer += pNumber<0?'1':'0';

	//Componentes
	std::string realBin = unum2bin(abs((long)pNumber), 0);
	std::string decimalBin = decimals2bin(pNumber);

	//Exponente
	int exponent;
	
	if (realBin[0] != '0'){
		exponent = realBin.length()-1;
	} else {
		exponent = -1 * (decimalBin.find('1') + 1);
	}
	exponent += 1023;
	buffer += unum2bin(exponent, 11);

	//Mantisa
	std::string mantissa = realBin + decimalBin;
	int start = mantissa.find('1');
	mantissa = mantissa.substr(start+1, mantissa.length() - start - 1);
	mantissa += multChar('0', 52 - mantissa.length());
	buffer += mantissa;

	return buffer;
}

unsigned long BaseConverter::to_ulong(std::string pBinary){
	unsigned long number = 0;
	for (int i = pBinary.length()-1, j = 0; i >= 0; i--, j++){
		number += (pBinary[i] - '0') * pow(2, j);
	}
	return number;
}

long BaseConverter::to_slong(std::string pBinary){
	if (pBinary[0] == '1'){
		pBinary = complement(pBinary);
		return -1 * to_ulong(pBinary);
	}
	return to_ulong(pBinary);
}

double BaseConverter::toDouble(std::string pBinary){
	//Dividir componentes
	std::string exponentBin = pBinary.substr(1, 11);
	std::string mantissaBin = pBinary.substr(12, 52);

	//Exponente
	short exponent = to_ulong(exponentBin);
	exponent -= 1023;

	//Valor binario y componentes
	mantissaBin = "1" + mantissaBin;
	std::string realPart;
	std::string decimalPart;

	if (exponent >= 0){
		realPart = mantissaBin.substr(0, exponent+1);
		decimalPart = mantissaBin.substr(exponent+1, 52-exponent-1);
	} else {
		realPart = "0";
		decimalPart = multChar('0', abs(exponent+1)) + mantissaBin;
	}

	double number = decimalsBin2double(decimalPart);

	number += to_ulong(realPart);
	number *= pBinary[0] == '0'?1:-1;

	return number;
}

std::string BaseConverter::complement(std::string pBits){
	for (int i = 0; i < pBits.length(); i++){
		pBits[i] = pBits[i]=='0'?'1':'0';
	}
	return pBits;
}

std::string BaseConverter::multChar(char pChar, int pCount){
	std::string buffer = "";
	for (int i = 0; i < pCount; i++){
		buffer += pChar;
	}
	return buffer;
}

std::string BaseConverter::decimals2bin(double pNumber){
	std::string buffer;
	double realPart = 0;
	pNumber = modf(pNumber, &realPart);
	realPart = 0;

	while (true){
		pNumber = modf(pNumber*2, &realPart);
		buffer += std::to_string((bool)realPart);
		if (pNumber == 0.0){
			return buffer;
		}
	}
}

double BaseConverter::decimalsBin2double(std::string pBits){
	double decimals = 0;
	for (int i = 0, j = -1; i < pBits.length(); i++, j--){
		decimals += (pBits[i] - '0') * pow(2, j);
	}
	return decimals;
}
