
#ifndef SERVERCONSOLE
#define SERVERCONSOLE

#include <thread>
#include "generalmanager.h"

class GeneralManager;

class ServerConsole
{

public:
	ServerConsole(GeneralManager* pManager)
	{
		_manager = pManager;
		_onRun = true;
	}

	void start();
	void stop();

	std::thread* getThread() const {
		return _thread;
	}

private:
	void addDisk();
	void removeDisk();
	void createDiskGroup();
	void removeDiskGroup();
	void showDiskGroups();
	void showSpecificDiskGroup();
	void startDiskGroup();
	void stopDiskGroup();
	void exitSystem();

	
	static void callRun(ServerConsole* pConsole);
	void run();
	void title();
	bool _onRun;
	GeneralManager* _manager;
	std::thread* _thread;
};

#endif /* SERVERCONSOLE */