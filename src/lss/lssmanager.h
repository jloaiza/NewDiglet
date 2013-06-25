#ifndef LSSMANAGER
#define LSSMANAGER

#include <string>
#include "../structures/doublelinkedlist/doublelinkedlist.h"
#include "session.h"
#include "lss.h"

class LssConsole;
class LSSNetworkHandler;

/**
 * _lss lista de discos (LSS) en éste servidor de almacenamiento
 * _console instancia a la clase LssConsole
 * _networkHandler instancia a la clase LSSNetworkHandler
 * _disponibleID ids disponibles para usar como nombres de LSS (archivos reales) 
 */
class LssManager{
	
private:

	DoubleLinkedList<Lss, short>* _lss;
	DoubleLinkedList<Session, int>* _sessions;
	LssConsole* _console;
	LSSNetworkHandler* _networkHandler;
	int _lssCount;

	static LssManager* _instance;

	void loadDisks();

public:

	LssManager();

	int newSession();

	static LssManager* getInstance();

	Session* getSession(int pSessionID);
	
	Lss* getLss(short pID);
	
	void createDisk(int pFileSize, std::string pSecKey);
	
	void saveDisks();

	void eraseDisk(short pID, std::string pSecKey);
	
	void startSystem();

	void stopSystem();

	void showDisks();
};

#endif
