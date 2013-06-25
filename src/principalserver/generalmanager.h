#ifndef GENERALMANAGER
#define GENERALMANAGER

#include "../structures/avltree/avltree.h"
#include "diskgroup.h"
#include "../structures/avltree/avltree.h"
#include "servernetworkhandler.h"
#include "storageclient.h"
//#include "serverconsole.h"
#include "diskgroup.h"
#include "session.h"
#include "user.h"
#include "disk.h"
#include "user.h"

#include <string>
class ServerConsole;

class GeneralManager{
	
public:

	GeneralManager();

	//Operaciones con DiskGroups
	std::string getDiskGroupStatus(std::string pDiskGroupID);
	std::string getDiskGroups();
	void defineDiskGroup(int pRAID, int pBlockSize, std::string pID);
	void addLSS(std::string pDiskGroupID, std::string pIPToConnect, int pPort, short pDiskID, std::string pSecurityKey);
	void startDiskGroup(std::string pDiskGroupID);
	void stopDiskGroup(std::string pDiskGroupID);

	//Manager - en general
	void startSystem();
	void stopSystem();

	//Operaciones con usuarios
	Session* getSession(int pSessionID);
	int newSession(std::string pUser, std::string pDiskGroupID);
	void closeSession(int pSessionID);
	User* getUser(std::string pUser);
	void addUser(std::string pUser, std::string pSecKey);

	//Manager - en general
	void startSystem();
	void stopSystem();
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
	void saveDisks();
	void saveUsers();

	void saveDiskGroupsAux(TreeNode<DiskGroup>* pNode);
	void saveClientsAux(TreeNode<StorageClient>* pNode);	
	void saveDisksAux(TreeNode<Disk>* pNode);
	void saveUsersAux(TreeNode<User>* pNode);

	std::string getDiskGroupsAux(TreeNode<Disk>* pNode);

	ServerNetworkHandler* _server; 						//Server para usuarios finales
	ServerConsole* _console; 							//Consola del sistema para administración
	AVLTree<DiskGroup, std::string>* _diskGroups; 		//Árbol que contiene los grupos de discos
	AVLTree<StorageClient, std::string>* _clientsTree; 	//Árbol utilizado para almacenar los clientes a los LSS
	AVLTree<Session, int>* _sessions;					//Árbol que contiene las sesiones actuales
	AVLTree<Disk, std::string>* _diskTree;				//Árbol que contiene los discos 
	AVLTree<User, std::string>* _userTree;				//Árbol que contiene los discos 
};

#endif /* GENERALMANAGER */
