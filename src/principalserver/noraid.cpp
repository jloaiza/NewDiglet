#include "noraid.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 		PRIVATE		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void NoRaid::eraseFile(iFile* pFile)
{
	
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 		PUBLIC		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

NoRaid::NoRaid(std::string pID, int pBlockSize)
{

}

NoRaid::NoRaid(std::string pID, int pBlockSize, int pMaxSize, bool pFunctional, bool pWorking)
{

}

SimpleList* NoRaid::Register2binary (RegisterSpace* pRegister, short pMetadataNumber, SimpleList* pBloques)
{
	short RegSize = pRegister->getRegisterSize(); /* tamaño de cada registro */
	short CantidadMetadatos = pRegister->getLength(); /* cantidad de metadatos */
	
	if ( pMetadataNumber == CantidadMetadatos) /* si metadatos insertados es igual a los metadatos totales */
	{
		return pBloques;
	}
	else /* aun quedan metadatos por escribir */
	{
		std::string block;	/* bloque para escribir en el disco */
		for (int x=0; x<24+RegSize; x++) { block += BytesHandler::snum2bin(0,1); }
		RegisterSpace* temporal = pRegister; /* apuntador a cada metadato */
		short aum = 0; /* numero de metadato */
		while ( aum*RegSize > _BlockSize-44)
		{
			std::string name = temporal->getName(); /* nombre del metadato */
			short type = temporal->getType(); /* tipo del metadato */
			short size = temporal->getSize(); /* tamaño del metadato */
			std::string data; /* metadato temporal en binario */
			data += BytesHandler::string2bin(name, size); /* nombre a binario */
			data += BytesHandler::snum2bin(type, 2); /* tipo a binario */
			data += BytesHandler::snum2bin(size, 2); /* size a binario */
			block += data; /* agregar el metadato temporal (binario) al bloque total */
			temporal = temporal->getNext(); /* moverse al siguiente metadato */
			aum++;
		}		
		pBloques->insertHead(block); /* inserta el bloque en la lista */
		return Register2binary(temporal, pMetadataNumber+aum, pBloques); 
	}
}

/* operaciones sobre el arbol n-ario */

DataNode * NoRaid::getFile(iFile* pFile)
{
	RegisterBuffer * temporal = pFile->getFileMetadata();
	return pFile->getFileData(temporal);
}

void NoRaid::startDiskGroup()
{

}
	
void NoRaid::stopDiskGroup()
{

}

void NoRaid::deleteFile(nTreeNode* pNode)
{
	iFile * temporal = pNode->getFile();
	temporal->~iFile;
	_files->erase(pNode);
}

nTreeNode * NoRaid::createFile(nTreeNode* pNode, std::string pName, RegisterSpace* pRegister, std::string pUser)
{
	Disk* disco = (Disk*) _diskList->getHead();
	
	short firstMetadata = 0; /* direccion del primer bloque de metadatos */
	
	short direccionAnterior = 0;
	std::string * anterior = new std::string(); /* apuntador a los datos del ultimo bloque escrito */
	std::string * blockTemporal = new std::string(); /* apuntador a los datos del ultimo bloque*/ 
	
	SimpleList* lista = Register2binary(pRegister); /*  crea los binarios de cada bloque de metadatos */ 
	Node * temporal = lista->_head; /* primer bloque de metadatos */
	anterior = 0; /* no hay ningun bloque insertado */
	while (temporal!=0) /* mientras que la lista contenga otro bloque de metadatos */
	{
		blockTemporal = (std::string*) temporal->data; /* bloque que vamos a escribir */
		short direccion = _diskList->writeBlock(*block); /* direccion en la cual escribimos el bloque */
		
		if (anterior == 0) /* si aun no hay bloque anterior */
		{
			anterior = blockTemporal;
			while (disco->full == true) { disco->getNext(); } /* itere hasta encontrar un disco con espacio */
			iFile* tmp = new iFile(disco->getDiskID(), direccion); /* crear el iFile */
			direccionAnterior = direccion;
		}
		else
		{
			std::string data = BytesHandler::string2bin(0, 10, size, data);	//reparar la direccion
			/* escribir en el bloque anterior la direccion del actual */
			_diskList->writeBytes(direccionAnterior, 0, 10, data); 
			
		}
	}
	
	iFile * temporal = new iFile( iFile(pName, 0, _blockSize, 0);
	temporal->createFile(pRegister);
	_files->insert(temporal, pNode, pName, pUser, "");
}





/* operaciones sobre el registros */

short NoRaid::apendReg(DataNode* pData, iFile* pFile)
{
	std::string diskID = pFile->getDisk();
}

short NoRaid::writeReg(int pRegisterNumber, DataNode* pData, iFile* pFile)
{

}

DataBuffer* NoRaid::readReg(int pRegisterNumber, iFile* pFile)
{

}

void NoRaid::eraseReg(int pRegisterNumber, iFile* pFile)
{

}

RegisterBuffer* NoRaid::getRegFormat(iFile* pFile)
{

}

/* operaciones administrativas */

void NoRaid::format()
{
	
}

/* operaciones sobre discos */

std::string NoRaid::toBinario(DataNode* pData)
{
	
}
