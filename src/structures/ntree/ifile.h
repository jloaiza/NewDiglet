#ifndef IFILE_H
#define IFILE_H

#include <string>
#include <iostream>
#include "../../include/comparable.h"
#include "../../principalserver/blockdirection.h"
#include "../../lss/lss.h"
#include "../../principalserver/databuffer.h"
#include "../../principalserver/registerbuffer.h"
#include "../../binaryoperations/byteshandler.h"

class iFile : public Comparable
{

private:

    BlockDirection* _FirstBlock;
    std::string _name;
    int _BlockSize;    
	Lss* _LSS;

    void getMetadata(char* pBlock, RegisterBuffer * pBuffer);
    void getData(char* pBlock, DataBuffer * pBuffer, RegisterBuffer * pMetadatos);
    
public:

    /**
     * @param pName nombre del archivo
     * @param pDirection direccion del primer bloque del archivo
     * @param pBlockSize tamaño de cada bloque
     * @param pDisk disco del archivo
     */
    iFile(std::string pName, BlockDirection* pDirection, int pBlockSize, Lss * pDisk);

    /**
     * @return direccion del primer bloque del archivo
     */
    BlockDirection* getDirection();

    /**
     * @param pDirection direccion del primer bloque del archivo
     */
    void setStartBlock(BlockDirection* pDirection);
    
    std::string getName();
    
    int getBlockSize();
    
    RegisterBuffer * getFileMetadata();
    
    DataBuffer * getFileData(RegisterBuffer * pMetadatos);
	
	

    /** INHERITANCE FROM COMPARABLE **/

    bool eql(Comparable* arg);
    bool gtr(Comparable* arg);
    bool lss(Comparable* arg);
    void print();

};

#endif // IFILE_H
