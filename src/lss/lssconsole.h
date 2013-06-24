#ifndef LSSCONSOLE
#define LSSCONSOLE

#include <thread>
#include "lssmanager.h"

class LssManager;

class LssConsole{
public:

	LssConsole(LssManager* pDiskManager){
		_diskManager = pDiskManager;
		_onRun = true;
	}

	void start();
	void stop();
	
	std::thread* getThread() const {
		return _thread;
	}

private:
	static void callRun(LssConsole* pConsole);
	void run();
	void title();
	bool _onRun;
	std::thread* _thread;
	LssManager* _diskManager;
};



#endif
