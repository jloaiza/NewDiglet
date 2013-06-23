#include "ifile.h"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 		PRIVATE		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void iFile::getMetadata(char* pBlock, RegisterBuffer * pBuffer)
{
	short bloque; /* numero de metadato que estamos leyendo */
	while (bloque*20 > _BlockSize-24) /* mientras aun haya otro metadato en el bloque */
	{
		std::string NOMBRE; /* nombre del metadato */
		for (int x=0; x<16; x++) { NOMBRE[x] = pBlock[(bloque*20)+24+x]; }
		char * TAMANO = new char[2]; /* tamaño del metadato */
		for (int z=0; z<2; z++) { TAMANO[z] = pBlock[(bloque*20)+24+16+z]; }
		short tamano = BytesHandler::to_ulong( BytesHandler::string2bin(std::string(TAMANO,2), 2) );
		char * TIPO = new char[2]; /* tipo del metadato */
		for (int y=0; y<2; y++) { TIPO[y] = pBlock[(bloque*20)+24+18+y]; }
		short tipo = BytesHandler::to_ulong( BytesHandler::string2bin(std::string(TIPO,2), 2) );
		pBuffer->addSpace(NOMBRE, tamano, tipo); /* agregar el metadato al buffer de metadatos */
		bloque++; /* siguiente bloque */
	}
}

void iFile::getData(char* pBlock, DataBuffer * pBuffer, RegisterBuffer * pMetadatos)
{
	
	short RegisterSize = pMetadatos->getLength(); /* tamaño de cada registro */
	short registro = 1; /* numero de registro que estamos leyendo */
	while (registro*RegisterSize > _BlockSize-10) /* mientras aun haya otro dato en el bloque */
	{
		RegisterSpace * temporal = pMetadatos->getBuffer(); /* metadato temporal para */
		
		short acum = 0; /* bytes leidos */
		for (int x=0; x<RegisterSize; x++) /* mientras que hayan mas metadatos */
		{
			short size = temporal->getSize(); /* tamaño del metadato */
			
			char* data = new char[size];
			for (int z=0; z<size; z++) { data[z] = pBlock[10+(registro*RegisterSize)+acum]; } /* copia los bytes del dato */
			acum += size; /* sumarle el tamaño del dato a los bytes acumulados */
			short type = temporal->getType(); /* tipo del metadato */
			void* dato; /* puntero al dato almacenado */
			if (type==1) /* si el dato es un bool */
			{ 
				bool datoTmp = ( (int) data[0]);
				dato = &datoTmp; 
			}
			else if (type==2) /* si el dato es un char */
			{
				dato = data;
			}
			else if (type==3) /* si el dato es un short */
			{
				short datoTmp = BytesHandler::to_ulong( BytesHandler::string2bin(std::string(data,2), 2) );
				dato = &datoTmp;
			}
			else if (type==4) /* si el dato es un int */
			{
				int datoTmp = BytesHandler::to_ulong( BytesHandler::string2bin(std::string(data,4), 4) );
				dato = &datoTmp;
			}
			else if (type==5) /* si el dato es un double */
			{
				double datoTmp = BytesHandler::toDouble( BytesHandler::string2bin(std::string(data,4), 4) );
				dato = &datoTmp;
			}
			else /* si el dato es un string */
			{
				std::string datoTmp = std::string(data,4);
				dato = &datoTmp;
			}
			
			pBuffer->addToBuffer(dato, type, size);
			temporal->getNext();
		}
		registro++;
	}
}

char * iFile::string_2_charArray(std::string pString, short pSize)
{
	char * temporal = new char[pSize];
	
	for (int x=0; x<pSize; x++)
	{
		temporal[x] = pString[x];
	}
	return temporal;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 		PUBLIC		* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

iFile::iFile(std::string pName, BlockDirection * pDirection, int pBlockSize, Lss * pDisk)
{
	_BlockSize = pBlockSize;
	_name = pName;
	_FirstBlock = pDirection;
	_LSS = pDisk;
	_LastRegister = 0;
}


BlockDirection* iFile::getDirection()
{
	return _FirstBlock;
}

void iFile::setStartBlock(BlockDirection* pDirection)
{
	_FirstBlock = pDirection;
}
    
std::string iFile::getName()
{
	return _name;
}
    
int iFile::getBlockSize()
{
	return _BlockSize;
}
    
RegisterBuffer * iFile::getFileMetadata()
{
	RegisterBuffer * MetadataNodes = new RegisterBuffer();	/* lista de Matadatos */
	char* BloqueM1 = _LSS->readA(_FirstBlock->getBlock());	/* lee el primer bloque de metadatos */
	char* BloqueM2 = new char[10];	/* apuntador al siguiente bloque de matadatos */
	for (int x=0; x<10; x++) { BloqueM2[x] = BloqueM1[x]; }
	BlockDirection * BM2ptr = new BlockDirection(BloqueM2); /* direccion al segundo bloque de metadatos */
	if (BM2ptr->getBlock() == 0) /* no hay un segundo bloque de metadatos */
	{
		getMetadata(BloqueM1, MetadataNodes); /* extraer los metadatos del unico bloque existente */
	}
	else /* hay otros bloques de metadatos */
	{
		while(true)
		{
			char * BloqueTmp = _LSS->readA(BM2ptr->getBlock());  /* leer el siguiente bloque de metadatos */
			char* BloqueTmp2 = new char[10]; /* apuntador al siguiente bloque de metadatos */
			for (int x=0; x<10; x++) { BloqueTmp2[x] = BloqueTmp[x]; }
			BlockDirection* BTmp2ptr = new BlockDirection(BloqueTmp2); /* direccion al siguiente bloque de metadatos */
			getMetadata(BloqueTmp, MetadataNodes); /* extraer los metadatos del bloque */
			if (BTmp2ptr->getBlock() == 0) /* era el ultimo bloque de metadatos */
			{
				break;
			}
			else /* aun quedan bloques de metadatos*/
			{
				BM2ptr = BTmp2ptr; /* siquiente bloque de metadatos */
			}
		}
	}
	return MetadataNodes;	
}
    
DataBuffer * iFile::getFileData(RegisterBuffer * pMetadatos)
{
	DataBuffer * DataNodes = new DataBuffer();	/* lista de DataNodes */
	char* BloqueM1 = _LSS->readA(_FirstBlock->getBlock());	/* lee el primer bloque de metadatos */
	char* BloqueD1ptr = new char[10];	/* apuntador al primer bloque de datos */
	for (int x=0; x<10; x++) { BloqueD1ptr[x] = BloqueM1[10+x]; }
	BlockDirection * BD1ptr = new BlockDirection(BloqueD1ptr); /* direccion al primer bloque de datos */
	char* BloqueD1 = _LSS->readA(BD1ptr->getBlock()); /* primer bloque de datos */
	char* BloqueD2 = new char[10];
	for (int y=0; y<10; y++) { BloqueD2[y] = BloqueD1[y]; }
	BlockDirection * BD2ptr = new BlockDirection(BloqueD2); /* direccion al segundo bloque de datos */
	if (BD2ptr->getBlock() == 0) /* no hay un segundo bloque de datos */
	{
		getData(BloqueD1, DataNodes, pMetadatos); /* extraer los datos del unico bloque existente */
	}
	else /* hay otros bloques de datos */
	{
		while(true)
		{
			char * BloqueTmp = _LSS->readA(BD2ptr->getBlock());  /* leer el siguiente bloque de datos */
			char* BloqueTmp2 = new char[10]; /* apuntador al siguiente bloque de datos */
			for (int x=0; x<10; x++) { BloqueTmp2[x] = BloqueTmp[x]; }
			BlockDirection* BTmp2ptr = new BlockDirection(BloqueTmp2); /* direccion al siguiente bloque de datos */
			getData(BloqueTmp, DataNodes, pMetadatos); /* extraer los datos del bloque */
			if (BTmp2ptr->getBlock() == 0) /* era el ultimo bloque de datos */
			{
				break;
			}
			else /* aun quedan bloques de datos*/
			{
				BD2ptr = BTmp2ptr; /* siquiente bloque de datos */
			}
		}
	}
	return DataNodes;
}

void iFile::apendReg(DataNode* pData)
{
	RegisterBuffer* Metadatos = getFileMetadata(); /* obtiene los metadatos del archivo */
	short RegisterSize = Metadatos->getLength(); /* tamaño de cada registro */
	
	char* BloqueM1 = _LSS->readA(_FirstBlock->getBlock()); /* bloque de metadatos */
	char* BloqueD1ptr = new char[10];	/* apuntador al primer bloque de datos */
	for (int x=0; x<10; x++) { BloqueD1ptr[x] = BloqueM1[32+x]; }
	BlockDirection * BD1ptr = new BlockDirection(BloqueD1ptr); /* direccion al primer bloque de datos */
	
	char* _register = new char[2]; _register[0]=BloqueM1[40]; _register[1]=BloqueM1[41];
	/* direccion del ultimo registro libre */
	short FreeRegister =  BytesHandler::to_ulong( BytesHandler::string2bin(std::string(_register,2), 2) ); 
	
	char* BloqueD1 = _LSS->readA(BD1ptr->getBlock()); /* primer bloque de datos */
	
	short type = pData->getType();
	short size = pData->getSize();
	std::string dato;
	
	if (type==1) /* si el dato es un bool */
	{ 
		dato = BytesHandler::snum2bin(pData->getData(), 1);
	}
	else if (type==2) /* si el dato es un char */
	{
		char* temporal = pData->getData();
		dato[0] = temporal[0];
	}
	else if (type==3) /* si el dato es un short */
	{
		dato = BytesHandler::snum2bin(pData->getData(), 2);
	}
	else if (type==4) /* si el dato es un int */
	{
		dato = BytesHandler::snum2bin(pData->getData(), 4);
	}
	else if (type==5) /* si el dato es un double */
	{
		dato = BytesHandler::double2bin(pData->getData());
	}
	else /* si el dato es un string */
	{
		dato = BytesHandler::string2bin(pData->getData(), size);
	}
	
	_LSS->writeB(dato, 10+(FreeRegister*RegisterSize); 
	
}

void createFile(RegisterBuffer* pBuffer)
{
	short RegSize = pBuffer->getRegisterSize(); /* tamaño de cada registro */
	short CantidadMetadatos = pBuffer->getLength(); /* cantidad de metadatos */
	if ( CantidadMetadatos*RegSize > _BlockSize-44-RegSize ) /* los metadatos no caben en un solo bloque */
	{
	}
	else /* los metadatos caben en un solo bloque */
	{
		std::string block;	/* bloque para escribir en el disco */
		for (int x=0; x<24+RegSize; x++) { block[x] = 0; }
		
		RegisterSpace* temporal = pBuffer->getBuffer(); /* apuntador a cada metadato */
		short aum = 0; /* numero de metadato */
		while (aum < CantidadMetadatos) /* mientras que haya otro metadato */
		{
			std::string name = temporal->getName(); /* nombre del metadato */
			short type = temporal->getType(); /* tipo del metadato */
			short size = temporal->getSize(); /* tamaño del metadato */
			std::string data;
			data += BytesHandler::string2bin(name, size);
			data += BytesHandler::snum2bin(type, 2);
			data += BytesHandler::snum2bin(size, 2);
			block += data; /* agregar al bloque */
			temporal = temporal->getNext();
			aum++;
		}
		short NumeroBloque = writeA(block, 0);
	}
}

/** COMPARABLE INHERITANCE **/

bool iFile::eql(Comparable* arg){

    /** TODO **/
    return false;

}

bool iFile::gtr(Comparable *arg){

    /** TODO **/
    return false;

}

bool iFile::lss(Comparable *arg){

    /** TODO **/
    return false;

}

void iFile::print(){
    /** TODO **/
}
