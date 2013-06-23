#ifndef LSSCONSOLE
#define LSSCONSOLE

#include <thread>
#include "lssmanager.h"

class LssManager;

class LssConsole
{

public:

	LssConsole(LssManager* pDiskManager)
	{
		_diskManager = pDiskManager;
		_onRun = true;
	}

	void start();
	void stop();
	
	std::thread* getThread() const 
	{
		return _thread;
	}

private:

	static void callRun(LssConsole* pConsole);
	void run();
	void title();
	bool _onRun;
	std::thread* _thread;
	LssManager* _diskManager;
	
	std::string lssmenuL = "** * * * * * * * * * * * * * * * * *";
	std::string lssmenuS = "*                                  *";
	std::string lssmenu3 = "*     seleccione la operacion:     *";
	std::string lssmenu4 = "*       1. Crear disco nuevo       *";
	std::string lssmenu5 = "*       2. Borrar disco            *";
	std::string lssmenu6 = "*       3. Mostrar discos          *";
	std::string lssmenu7 = "*       4. SAVE                    *";
	std::string lssmenu8 = "*       5. LOAD                    *";
	std::string lssmenu9 = "*       6. Salir                   *";

	std::string NAME = "nombre del disco (archivo real): ";
	std::string NAME2 = "nombre del xml: ";
	std::string SIZE1 = "tamaño del disco (bytes): ";
	std::string PASS = "security key: ";

};



#endif
