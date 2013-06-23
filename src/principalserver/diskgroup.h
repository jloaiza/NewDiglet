#ifndef DISKGROUP
#define DISKGROUP

//#include "resgisterspacer.h"
//#include "../basicstructures/datanode.h"

class RegisterSpace;
class DataBuffer;
class DataNode;


class DiskGroup 
{
	
public:
	
	
	/* operaciones sobre el arbol n-ario */
	
	
	/**
	 * busca y retorna un archivo del disco
	 * @param pFile nombre del archivo que se cargará en memoria
	 * @return lista de DataNodes con la informacion del archivo
	 */
	virtual DataNode * getFile(iFile pFile) = 0;
	
	/**
	 * borra un archivo o una carpeta
	 * @param pNode nodo que se va a borrar
	 */
	virtual void deleteFile(nTreeNode* pNode) = 0;
	
	/**
	 * crea un nuevo archivo
	 * @param pName nombre o direccion del nuevo archivo o carpeta
	 * @param pRegister formato de cada registro del nuevo archivo
	 * @param pUser nombre del usuario que realiza la operacion
	 * @return nodo donde se creó el archivo
	 */
	virtual nTreeNode * createFile(std::string pName, pRegisterList pRegister, std::string pUser) = 0;
		
	/**
	 * busca un nodo con la direccion relativa
	 * @param pRelativePath direccion relativa del nodo que buscamos
	 */
	virtual nTreeNode* getNode(std::string pRelativePath, nTreeNode* pNode) = 0;
	
	
	/* operaciones sobre el registros */
	
	
	/**
	 * agrega un registro al final (despues del ultimo registro almacenado)
	 * @param pData datos que contiene el registro
	 * @return numero de registro
	 */
	virtual short apendReg(DataNode* pData, iFile* pFile) = 0;
	
	/**
	 * sobreescribe un registro
	 * @param pRegisterNumber numero de registro
	 * @param pData datos que contiene el registro
	 * @param pFile archivo en el cual se escribe el registro
	 * @return numero de registro
	 */
	virtual short writeReg(int pRegisterNumber, DataNode* pData, iFile* pFile) = 0;
	
	/**
	 * lee un registro 
	 * @param pRegisterNumber numero de registro
	 * @param pFile archivo de donde se va a leer el registro
	 * @return lista de dataNodes del registro
	 */	
	virtual DataNode* readReg(int pRegisterNumber, iFile* pFile) = 0;
	
	/**
	 * borra un registro
	 * @param pRegisterNumber numero de registro
	 * @param pFile archivo del cual se borrará un registro
	 */	
	virtual void eraseReg(int pRegisterNumber, iFile* pFile) = 0;
	
	/**
	 * retorna el formato del Registro
	 * @param pFile archivo del cual se quiere saber el formato
	 * @return tamaño, nombre y tipos de datos que contiene el registro
	 */
	virtual RegisterSpace* getRegFormat(iFile* pFile) = 0;
	
	
	/* operaciones administrativas */
	
	
	virtual format() = 0;
	
	virtual std::string getID() = 0;
	
	virtual int getBlockSize() = 0;
	
	virtual bool isWorking() = 0;
	
	virtual bool isFunctional() = 0;
	
		
	/* operaciones sobre discos */

	virtual SimpleList* getDiskList() = 0;
	
	virtual void addDisk(Disk* pDisk) = 0;
	
	virtual void removeDisk(std::string pIP, std::string pID) = 0;
	
	virtual void setBlockSize(int pSize) = 0;
		
	virtual std::string toBinario(DataNode* pData) = 0;


};

#endif
