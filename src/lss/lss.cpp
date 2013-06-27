#include <alloca.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "../binaryoperations/byteshandler.h"
#include "lss.h"

std::ostream& operator<<(std::ostream& out, Lss& pLss){
	out << "ID: " << pLss.getID() << " Size: " << pLss.getDiskSize();
	return out;
}

bool Lss::operator != (const short& pToCompare){
	return _id != pToCompare;
}

bool Lss::operator == (const short& pToCompare){
	return _id == pToCompare;
}

bool Lss::operator < (const short& pToCompare){
	return _id < pToCompare;
}

bool Lss::operator <= (const short& pToCompare){
	return _id <= pToCompare;
}

bool Lss::operator > (const short& pToCompare){
	return _id > pToCompare;
}

bool Lss::operator >= (const short& pToCompare){
	return _id >= pToCompare;
}


bool Lss::operator != (Lss& pToCompare){
	return _id != pToCompare.getID();
}

bool Lss::operator == (Lss& pToCompare){
	return _id == pToCompare.getID();
}

bool Lss::operator < (Lss& pToCompare){
	return _id < pToCompare.getID();
}

bool Lss::operator <= (Lss& pToCompare){
	return _id <= pToCompare.getID();
}

bool Lss::operator > (Lss& pToCompare){
	return _id > pToCompare.getID();
}

bool Lss::operator >= (Lss& pToCompare){
	return _id >= pToCompare.getID();
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 		PRIVATE		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void Lss::header()
{
	char * data = new char[12];
	for (int x=0; x<6; x++)
	{
		data[x]=0;
	}
	
	std::string tmp = BytesHandler::bin2str( BytesHandler::unum2bin(1, 2) );
	data[6] = tmp[0];
	data[7] = tmp[1];
	std::string tmp2 = BytesHandler::bin2str( BytesHandler::unum2bin(_size, 4) );
	data[8] = tmp2[0];
	data[9] = tmp2[1];
	data[10] = tmp2[2];
	data[11] = tmp2[3];
	std::ofstream File;	
	File.open( _disk.data() );
	File.write (data, _blockSize);
	File.close();
}

char * Lss::string_2_charArray(std::string pString, short pSize)
{
	char * temporal = new char[pSize];
	
	for (int x=0; x<pSize; x++)
	{
		temporal[x] = pString[x];
	}
	return temporal;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 		PUBLIC		 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

Lss::Lss(std::string pDisk, short pID, int pSize, std::string pSecKey)
{
	_disk = pDisk;
	_busy = false;
	_id = pID;
	_size = pSize;
	_blockSize = 12;
	_secKey = pSecKey;
	header();
}


int Lss::getID(){
	return _id;
}

short Lss::writeA (std::string pData)
{
	short freeblock = getFreeBlock(); 	/* pide un bloque borrado (en caso de que existan) */	
	if ( freeblock == 0)	/* no hay bloques borrados */
	{
		freeblock = getLastBlock(); 	/* pide el ultimo bloque libre */
		if (freeblock == 0) 	/* no hay espacio */
		{
			std::cout << "disco lleno";
		}
		else 	/* si hay espacio */
		{
			short nextDirection = freeblock+1;		/* numero del nuevo bloque libre */
			writeB ( BytesHandler::bin2str(BytesHandler::unum2bin(nextDirection, 2)), 6, 2); 	/* aumenta el apuntador al ultimo bloque libre */
			writeB (pData, 12+(freeblock*_blockSize), _blockSize);		/*	escribe los datos en la direccion del bloque libre */
		}
	}
	else 	/* si hay un bloque borrado disponible */
	{
		char * buffer = readB ( (12+(freeblock*_blockSize)), 2); /* lee la direccion del bloque borrado */
		short freeblock2 = BytesHandler::to_ulong( BytesHandler::string2bin(std::string(buffer,2), 2) );		/*	convierte la lectura a un short */
		std::cout << freeblock2 << std::endl;
		if (freeblock2 == 0) 	/* solo hay 1 bloque libre */ 
		{
			writeB ( BytesHandler::bin2str(BytesHandler::unum2bin(0, 2)), 4, 2);		/* apuntador a bloques borrados = NULL*/
		}
		else 	/* hay mas de un bloque libre */
		{
			writeB ( BytesHandler::bin2str(BytesHandler::unum2bin(freeblock2, 2)), 4, 2);		/* aumenta apuntador a bloques borrados */
		}
		
		writeB (pData, 12+(freeblock*_blockSize), _blockSize );		/* escribe los datos en el bloque borrado */
	}
	std::cout<<"Write A. Disk: '"<< _id<<"' freeblock: "<<freeblock<<std::endl;
	return freeblock;		/* numero de bloque donde escribio los datos*/
}

void Lss::writeC(std::string pData, int pBlock, int pOffset, int pSize){
	writeB(pData, (12+(pBlock*_blockSize))+pOffset, pSize);
}

void Lss::writeB (std::string pData, int pPos, int pSize)
{
	std::fstream File;
	File.open( _disk );
	File.seekp ( pPos, File.beg);
	File.write (string_2_charArray(pData, pSize), pSize);
	File.close();
}

char * Lss::readA (int pBlock)
{
	return readB ( (12+(pBlock*_blockSize)), _blockSize );
}

char * Lss::readC(int pBlock, int pOffset, int pSize){
	return readB ( (12+(pBlock*_blockSize))+pOffset, pSize );
}

char * Lss::readB (int pPos, int pSize)
{
	char * buffer = new char [pSize];
	std::ifstream File;
	File.open( _disk );
	File.seekg ( pPos, File.beg);
	File.read (buffer, pSize);
	File.close();
	return buffer;
}

bool Lss::isBusy(){
	return _busy;
}

short Lss::getFreeBlock()
{
	char * buffer = new char[2];
	buffer = readB (4, 2);
	short tmp2 = BytesHandler::to_ulong( BytesHandler::string2bin(std::string(buffer,2), 2) );
	return tmp2;
}

short Lss::getLastBlock()
{
	char * buffer = new char[2];
	buffer = readB (6, 2);
	short tmp2 = BytesHandler::to_ulong( BytesHandler::string2bin(std::string(buffer,2), 2) );
	return tmp2;	
}

int Lss::getBlockSize()
{
	return _blockSize;
}

int Lss::getDiskSize()
{
	return _size;
}

std::string Lss::getSecKey(){
	return _secKey;
}

void Lss::format(int pBlockSize)
{
	
}

void Lss::eraseBlock(int pBlock)
{
	short BloqueLibre = getFreeBlock();		/* numero del primer bloque borrado */
	
	char* tmp = new char[_blockSize];
	for (int x=0; x<_blockSize; x++) { tmp[x]=0; }
	
	if (BloqueLibre == 0)
	{
		writeB( BytesHandler::bin2str( BytesHandler::unum2bin(pBlock, 2) ), 4, 2);
		writeB( tmp, 12+(pBlock*_blockSize), _blockSize);
	}
	else
	{
		while(true)
		{
			short BloqueLibre2;
			char * buffer = new char[2];
			buffer = readB (12+(BloqueLibre*_blockSize), 2);
			BloqueLibre2 = BytesHandler::to_ulong( BytesHandler::string2bin(std::string(buffer,2), 2) );
			if (BloqueLibre2 == 0)
			{
				writeB( BytesHandler::bin2str( BytesHandler::unum2bin(pBlock, 2) ), 12+(BloqueLibre*_blockSize), 2);
				writeB( tmp, 12+(pBlock*_blockSize), _blockSize);
				break;
			}
			else
			{
				BloqueLibre = BloqueLibre2;
			}	
		}
	}
}
