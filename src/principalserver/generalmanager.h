#ifndef GENERALMANAGER
#define GENERALMANAGER

<<<<<<< HEAD
#include "../structures/avltree/avltree.h"
=======
#include "diskgroup.h"
#include "avltree/avltree.h"
>>>>>>> refs/heads/new-binaries-implementation
#include "servernetworkhandler.h"
#include "serverconsole.h"
#include "diskgroup.h"
#include "session.h"
#include "user.h"
#include "disk.h"
#include "user.h"

#include <string>

class StorageClient; //Esta clase aún no ha sido implementada. Cuando se encuentre lista, se debe quitar esta linea y hacer un include

class GeneralManager{
	
public:

	GeneralManager();
	std::string getDiskGroupStatus(std::string pDiskGroupID);
	Session* getSession(int pSessionID);
	int newSession(std::string pUser, std::string pDiskGroupID);
	void closeSession(int pSessionID);
	void defineDiskGroup(int pRAID, int pBlockSize, std::string pID);
	void addLSS(std::string pDiskGroupID, std::string pIPToConnect, int pPort, short pDiskID, std::string pSecurityKey);
	void startDiskGroup(std::string pDiskGroupID);
	void stopDiskGroup(std::string pDiskGroupID);
	void startSystem();
	void stopSystem();
	User* getUser(std::string pUser);
	void addUser(std::string pUser, std::string pSecKey);

	static GeneralManager* getInstance(){
		return _instance;
	}

private:
	static GeneralManager* _instance; //Pseudo-singleton
	
	void loadDiskGroups();
	void loadClients();
	void loadDisks();
	void loadUsers();

	void saveDiskGroups(); 
	void saveClients();	
	void saveDisk();
	void saveUsers();

	void saveDiskGroupsAux(TreeNode<DiskGroup>* pNode);
	void saveClientsAux(TreeNode<StorageClient>* pNode);	
	void saveDiskAux(TreeNode<Disk>* pNode);
	void saveUsersAux(TreeNode<User>* pNode);

	ServerNetworkHandler* _server; 						//Server para usuarios finales
	ServerConsole* _console; 							//Consola del sistema para administración
	AVLTree<DiskGroup, std::string>* _diskGroups; 		//Árbol que contiene los grupos de discos
	AVLTree<StorageClient, std::string>* _clientsTree; 	//Árbol utilizado para almacenar los clientes a los LSS
	AVLTree<Session, int>* _sessions;					//Árbol que contiene las sesiones actuales
<<<<<<< HEAD
	AVLTree<Disk, int>* _diskTree;						//Árbol que contiene los discos 
=======
	AVLTree<Disk, std::string>* _diskTree;				//Árbol que contiene los discos 
>>>>>>> refs/heads/new-binaries-implementation
	AVLTree<User, std::string>* _userTree;				//Árbol con que contiene a los usuarios
};

#endif /* GENERALMANAGER */
