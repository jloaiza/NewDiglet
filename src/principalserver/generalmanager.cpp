#include "generalmanager.h"
#include "../include/constants.h"
#include "../xml/clientsxml.h"
#include "../xml/diskgroupsxml.h"
#include "../xml/diskxml.h"
#include "../xml/usersxml.h"
#include "../tokenizer/tokenizer.h"
#include "serverconsole.h"
#include "noraid.h"
#include "raidzero.h"
#include "raidone.h"
#include "raidfive.h"

GeneralManager* GeneralManager::_instance = 0;

GeneralManager::GeneralManager(){
	_instance = this;

	_server = new ServerNetworkHandler();
	_console = new ServerConsole(this);

	_sessions = new AVLTree<Session, int>();
	_userTree = new AVLTree<User, std::string>;
	_diskTree = new AVLTree<Disk, std::string>;
	_clientsTree = new AVLTree<StorageClient, std::string>;
	_diskGroups = new AVLTree<DiskGroup, std::string>;
}

std::string GeneralManager::getDiskGroupStatus(std::string pDiskGroupID){
	DiskGroup* disk = _diskGroups->search( &pDiskGroupID );
	if (disk == 0){
		return "Disco no encontrado.\n";
	}
	std::string isWorking = disk->isWorking()?"true":"false";
	std::string isFunctional = disk->isFunctional()?"true":"false";
	std::string message = std::string("Disk ID: ") + pDiskGroupID + std::string(" working: ") + isWorking + std::string(" functional:") + isFunctional + std::string("\n");
	message += disk->getDiskList();
	return message;
}

std::string GeneralManager::getDiskGroupsAux(TreeNode<DiskGroup>* pNode){
	if (pNode == 0){
		return "";
	}
	std::string message = "";
	message += getDiskGroupsAux(pNode->getLeftChild());

	DiskGroup* disk = pNode->getData();
	std::string isWorking = disk->isWorking()?"true":"false";
	std::string isFunctional = disk->isFunctional()?"true":"false";
	message += std::string("Disk ID: ") + disk->getID() + std::string(" working: ") + isWorking + std::string(" functional:") + isFunctional + std::string("\n");
	message += "\n";

	message += getDiskGroupsAux(pNode->getRightChild());
	return message;
}

std::string GeneralManager::getDiskGroups(){
	return getDiskGroupsAux(_diskGroups->getRoot());
}

Session* GeneralManager::getSession(int pSessionID){
	return _sessions->search(&pSessionID);
}

int GeneralManager::newSession(std::string pUser, std::string pDiskGroupID){
	std::cout<<"New session disk id: "<<pDiskGroupID<<std::endl;
	DiskGroup* disk = _diskGroups->search( &pDiskGroupID );
	if (disk == 0){
		std::cout<<"bad disk"<<std::endl;
		return PS::NO_SESSION;
	} else {
		if (disk->isWorking()){
			Session* newSession = new Session(pUser, disk);
			_sessions->insert(newSession);
			return newSession->getSessionID();
		} else {
			return PS::NO_SESSION;
		}
	}
}

void GeneralManager::closeSession(int pSessionID){
	Session* session = _sessions->erase(&pSessionID);
	delete session;
}

User* GeneralManager::getUser(std::string pUser){
	return _userTree->search(&pUser);
}

void GeneralManager::addUser(std::string pUser, std::string pSecKey){
	User* user = new User(pUser, pSecKey);
	_userTree->insert(user);
}

void GeneralManager::defineDiskGroup(int pRAID, int pBlockSize, std::string pID){
	if (_diskGroups->search(&pID) != 0){
		std::cout<<"Error. Ya existe un DiskGroup con el identificador '" << pID << "'."<<std::endl;
	} else {
		switch (pRAID){
			case DiskGroup::NO_RAID:
				_diskGroups->insert(new NoRaid(pID, pBlockSize));
				break;

			case DiskGroup::RAID0:
				_diskGroups->insert(new RaidZero(pID, pBlockSize));
				break;

			case DiskGroup::RAID1:
				_diskGroups->insert(new RaidOne(pID, pBlockSize));
				break;

			case DiskGroup::RAID5:
				_diskGroups->insert(new RaidFive(pID, pBlockSize));
				break;

			default:
				std::cout<<"Error. El tipo RAID " << pRAID << " no existe."<<std::endl;
				break;
		}
	}
}

void GeneralManager::addLSS(std::string pDiskGroupID, std::string pIPToConnect, int pPort, short pDiskID, std::string pSecurityKey){
	//Busca si el disco ya existe
	std::string diskID = pIPToConnect + ":" + std::to_string(pDiskID);
	if (_diskTree->search(&diskID) != 0){
		std::cout<<"Error. El disco ya existe."<<std::endl;
		return;
	}
	
	//Busca el DiskGroup para agregar el disco
	DiskGroup* diskGroup = _diskGroups->search(&pDiskGroupID);
	if (diskGroup == 0){
		std::cout<<"Error. El DiskGroup especificado no existe."<<std::endl;
		return;
	}

	//Busca si el cliente existe, de no ser así, este es creado
	StorageClient* client = _clientsTree->search(&pIPToConnect);
	if (client == 0){
		client = new StorageClient(pIPToConnect, pPort);
		if (!client->isConnected()){
			std::cout<<"Error. No se pudo conectar con el LSS. El LSS se insertará pero no podrá ser utilizado hasta que el servidor esté online."<<std::endl;
		}
		_clientsTree->insert(client);
	}
	
	//Crea el disco y lo inserta
	Disk* disk = new Disk(client, pDiskID, pSecurityKey); // Al crear el disco el se conecta automaticamente

	if (!disk->isAlive()){
		std::cout<<"Error. El disco no está disponible. Este será insertado pero no podrá ser utilizado hasta que se encuentre online."<<std::endl;
	}
	
	_diskTree->insert(disk);
	diskGroup->addDisk(disk);
}

void GeneralManager::startDiskGroup(std::string pDiskGroupID){
	DiskGroup* diskGroup = _diskGroups->search(&pDiskGroupID);
	if (diskGroup == 0){
		std::cout<<"Error. El DiskGroup especificado no existe."<<std::endl;
	} else if (!diskGroup->isWorking()){
		if (diskGroup->isFunctional()){
			diskGroup->startDiskGroup();
		} else {
			char format = 'n';
			std::cout<<"El DiskGroup ha sufrido cambios importantes y se debe formatear, ¿desea continuar? (y/n): ";
			std::cin>>format;
			std::cout<<std::endl;
			if (format == 'y'){
				diskGroup->format();
				diskGroup->startDiskGroup();
			}
		}
	}
}

void GeneralManager::stopDiskGroup(std::string pDiskGroupID){
	DiskGroup* diskGroup = _diskGroups->search(&pDiskGroupID);
	if (diskGroup == 0){
		std::cout<<"Error. El DiskGroup especificado no existe."<<std::endl;
	} else if (diskGroup->isWorking()){
		char stop = 'n';
		std::cout<<"Esta operación deshablitará el DiskGroup y no podrá ser utilizado hasta que se inicie de nuevo, ¿Desea continuar? (y/n): ";
		std::cin>>stop;
		std::cout<<std::endl;
		if (stop == 'y'){
			diskGroup->stopDiskGroup();
		}
	}
}

void GeneralManager::loadDiskGroups(){
	if (!parserxml::thereFile("raidb/diskgroups.xml")){
		diskgroupsxml::createXMLFile("raidb/diskgroups.xml");
	}
	std::string raidType = diskgroupsxml::getDiskGroupRaid("raidb/diskgroups.xml", 1);
	for (int i = 1; raidType != ""; i++){

		//Obtener los atributos del diskgroup
		std::string id = diskgroupsxml::getDiskGroupId("raidb/diskgroups.xml", i);
		int blockSize = std::stoi( diskgroupsxml::getDiskGroupBlockSize("raidb/diskgroups.xml", i) );
		int maxSize = std::stoi( diskgroupsxml::getDiskGroupMaxSize("raidb/diskgroups.xml", i) );
		bool functional = diskgroupsxml::getDiskGroupFunctional("raidb/diskgroups.xml", i) == "true"?true:false;
		bool working = diskgroupsxml::getDiskGroupWorking("raidb/diskgroups.xml", i) == "true"?true:false;

		//Inicializar el diskgroup
		DiskGroup* diskGroup = 0;
		if (raidType == std::to_string(DiskGroup::NO_RAID)){
			diskGroup = new NoRaid(id, blockSize, maxSize, functional, working);
		} else if (raidType == std::to_string(DiskGroup::RAID0)){
			diskGroup = new RaidZero(id, blockSize, maxSize, functional, working);
		} else if (raidType == std::to_string(DiskGroup::RAID1)){
			diskGroup = new RaidOne(id, blockSize, maxSize, functional, working);
		} else if (raidType == std::to_string(DiskGroup::RAID5)){
			diskGroup = new RaidFive(id, blockSize, maxSize, functional, working);
		}

		//Cargar discos
		std::string diskID = diskgroupsxml::getDiskGroupDiskId("raidb/diskgroups.xml", i, 0);
		for (int j = 1; diskID != ""; j++){

			std::string clientPath = Tokenizer::getCommandSpace(diskID, 0, ':');
			StorageClient* client = _clientsTree->search( &clientPath );

			Disk* disk = client->getDisk( std::stoi(Tokenizer::getCommandSpace(diskID, 1, ':')) );
			diskGroup->addDisk(disk);
			diskID = diskgroupsxml::getDiskGroupDiskId("raidb/diskgroups.xml", i, j+1);
		}

		_diskGroups->insert(diskGroup);
		std::cout<<"Diskgroup '"<<id<<"' añadido con éxito"<<std::endl;

		raidType = diskgroupsxml::getDiskGroupRaid("raidb/diskgroups.xml", i+1);
	}
}

void GeneralManager::loadClients(){
	if (!parserxml::thereFile("raidb/clients.xml")){
		clientsxml::createXMLFile("raidb/clients.xml");
	}
	std::string ip = clientsxml::getClientIp("raidb/clients.xml", 1);
	std::cout<<"xml opened: "<<ip<<std::endl;
	for (int i = 1; ip != ""; i++){
		int port = std::stoi(clientsxml::getClientPort("raidb/clients.xml", i));
		StorageClient* client = new StorageClient(ip, port);
		_clientsTree->insert(client);
		ip = clientsxml::getClientIp("raidb/clients.xml", i+1);
	}
}

void GeneralManager::loadDisks(){
	if (!parserxml::thereFile("raidb/disks.xml")){
		DiskXML::createXMLFile("raidb/disks.xml");
	}
	std::string id = DiskXML::getIdDisk("raidb/disks.xml", 1);
	for (int i = 1; id != ""; i++){

		std::string clientIP = DiskXML::getClientDisk("raidb/disks.xml", i);
		StorageClient* client = _clientsTree->search(&clientIP);

		std::string secKey = DiskXML::getSecurityKey("raidb/disks.xml", i);

		Disk* disk = new Disk(client, std::stoi(id), secKey);
		_diskTree->insert(disk);

		id = std::stoi( DiskXML::getIdDisk("raidb/disks.xml", i+1) );
	}
}

void GeneralManager::loadUsers(){
	if (!parserxml::thereFile("raidb/users.xml")){
		usersxml::createXMLFile("raidb/users.xml");
	}
	std::string id = usersxml::getIdUser("raidb/users.xml", 1);
	for (int i = 1; id != ""; i++){
		std::string secKey = usersxml::getSecurityKey("raidb/users.xml", i);
		User* user = new User(id, secKey);
		_userTree->insert(user);
		id = usersxml::getIdUser("raidb/users.xml", i+1);
	}
}

void GeneralManager::saveDiskGroups(){
	saveDiskGroupsAux(_diskGroups->getRoot());
}

void GeneralManager::saveClients(){
	saveClientsAux(_clientsTree->getRoot());
}

void GeneralManager::saveDisks(){
	saveDisksAux(_diskTree->getRoot());
}

void GeneralManager::saveUsers(){
	saveUsersAux(_userTree->getRoot());
}

void GeneralManager::saveDiskGroupsAux(TreeNode<DiskGroup>* pNode){

}

void GeneralManager::saveClientsAux(TreeNode<StorageClient>* pNode){

}

void GeneralManager::saveDisksAux(TreeNode<Disk>* pNode){

}

void GeneralManager::saveUsersAux(TreeNode<User>* pNode){

}

void GeneralManager::startSystem(){
	/* CUIDADO EL ORDEN DE INICIALIZACIÓN DEBE SER:
	1. CLIENTES
	2. DISCOS
	3. DISKGROUPS
	*/
	loadClients();
	std::cout<<"clients loaded"<<std::endl;
	loadDisks();
	std::cout<<"disks loaded"<<std::endl;
	loadDiskGroups();
	std::cout<<"groups loaded"<<std::endl;
	loadUsers();
	std::cout<<"users loaded"<<std::endl;

	_console->start();
	_server->start();
	_console->getThread()->join();
	_server->getThread()->join();
}

void GeneralManager::stopSystem(){
	saveClients();
	saveDisks();
	saveDiskGroups();
	saveUsers();

	_console->stop();
	_server->closeServer();
}