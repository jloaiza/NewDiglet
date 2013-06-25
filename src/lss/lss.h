#ifndef LSS
#define LSS

#include "../include/comparable.h"
#include <string>

class Lss : public Comparable {
	
private:

	std::string TWOPOINTS = ":";
	std::string DIRECTION = "@";	
    std::string _disk;
	bool _busy;
	int _size;
	int _blockSize;
	short _id;
	std::string _secKey;
	
	/**
	 * construye el header del lss (binario)
	 */
	void header();
	
	char * string_2_charArray(std::string pString, short pSize);
	
public:

    Lss(std::string pDisk, short pID, int pSize, std::string pSecKey);

	/**
	 * escribe en el disco
	 * @param pData informacion que escribiremos en el LSS
	 * @param pBlockPadre bloque del predecesor, en caso de que exista algun bloque relacionado con éste nuevo bloque
	 * @return numero de bloque donde escribimos
	 * @version 2.0 	se implemento para que busque un bloque libre, y retorne el numero de bloque que se utilizo
	 */
	short writeA (std::string pData);
	
	/**
	 * escribe cualquier cantidad de caracteres en cualquier posicion del LSS
	 * @param pData datos que se escriben en el disco
	 * @param pPos posicion especifica en el disco
	 * @param pSize cantidad de caracteres que se van a escribir
	 */
	void writeB (std::string pData, int pPos, int pSize);
	
	/**
	 * @param pBlock bloque que se va a leer
	 * @return datos leidos
	 */
	char * readA (int pBlock);
	
	/**
	 * lee cualquier cantidad de caracteres en cualquier posicion del disco
	 * @param pPos posicion dentro del disco
	 * @param pSize cantidad de caracteres que se van a leer
	 * @return datos que leyó del disco
	 */
	char * readB (int pPos, int pSize);
	
	/**
	 * @return numero del bloque libre
	 */
	short getFreeBlock();
	
	short getLastBlock();
	
	int getBlockSize();
	
	int getDiskSize();
	
	std::string getSecKey();
	
	/**
	 * formatea el disco; borrando los datos y estableciendo un nuevo tamaño de bloque
	 * @param pBlockSize nuevo tamaño del bloque 
	 */
	void format(int pBlockSize);

	
	void eraseBlock(int pBlock);


	
	bool eql(Comparable* arg);
	bool gtr(Comparable* arg);
	bool lss(Comparable* arg);
	void print();

	bool operator != (const short& pToCompare);
	bool operator == (const short& pToCompare);
	bool operator < (const short& pToCompare);
	bool operator <= (const short& pToCompare);
	bool operator > (const short& pToCompare);
	bool operator >= (const short& pToCompare);

};

#endif
