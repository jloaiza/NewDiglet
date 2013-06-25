#ifndef DISKGROUP
#define DISKGROUP


#include "registerspace.h"
#include "datanode.h"
#include "disk.h"
#include "../structures/doublelinkedlist/doublelinkedlist.h"
#include "../structures/ntree/ntree.h"
#include "../structures/ntree/ntreenode.h"
#include "../structures/ntree/ifile.h"

#include <string>

class DiskGroup
{
	
public:
	
	static const int NO_RAID = -1;
	static const int RAID0 = 0;
	static const int RAID1 = 1;
	static const int RAID5 = 5;

	bool operator==(std::string& pID);
	bool operator>(std::string& pID);
	bool operator>=(std::string& pID);
	bool operator<(std::string& pID);
	bool operator<=(std::string& pID);
	bool operator!=(std::string& pID);

	bool operator==(DiskGroup& pDiskGroup);
	bool operator>(DiskGroup& pDiskGroup);
	bool operator>=(DiskGroup& pDiskGroup);
	bool operator<(DiskGroup& pDiskGroup);
	bool operator<=(DiskGroup& pDiskGroup);
	bool operator!=(DiskGroup& pDiskGroup);

	/* operaciones sobre el arbol n-ario */
	
	/**
	 * busca y retorna un archivo del disco
	 * @param pFile nombre del archivo que se cargará en memoria
	 * @return lista de DataNodes con la informacion del archivo
	 */
	virtual DataNode* getFile(iFile* pFile) = 0;
	
	virtual void startDiskGroup() = 0;

	virtual void stopDiskGroup() = 0;

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
	virtual nTreeNode* createFile(nTreeNode* pActual, std::string pName, RegisterSpace* pRegister, std::string pUser) = 0;	
	
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
	
	virtual void format() = 0;
	
	std::string getID() const {
		return _id;
	}

	/**
	 * busca un nodo con la direccion relativa
	 * @param pRelativePath direccion relativa del nodo que buscamos
	 */
	nTreeNode* getNode(std::string pRelativePath, nTreeNode* pNode);
	
	int getBlockSize() const {
		return _blockSize;
	}

	void setBlockSize(int pSize){
		_blockSize = pSize;
		_functional = false;
		_working = false;
	}
	
	bool isWorking() const {
		return _working;
	}

	bool isFunctional(){
		return _functional;
	}
	
	void createDir(nTreeNode* pFolderNode, std::string pName, std::string pUser);
		
	/* operaciones sobre discos */

	std::string getDiskList();
	
	void addDisk(Disk* pDisk);
	
	void removeDisk(std::string pIP, short pID);

	void loadTree(std::string pTreePath);
		
	std::string toBinary(DataNode* pData);

	DataNode* toDataNode(RegisterSpace* pRegister, int pColNameSize, int pTypeSize, int pDataSize);

	ListNode<std::string>* getStrips(std::string pMessage, int pBlockSize);

protected:
	
	std::string _id;
	nTree* _files;
	int _raid;
	int _blockSize;
	int _maxSize;
	bool _functional;
	bool _working;
	DoubleLinkedList<Disk, std::string>* _diskList;

	virtual void eraseFile(iFile* pFile) = 0;



};

#endif
