#include "serverconsole.h"

#include <iostream>
#include <string>
#include "info.h"

static void LssConsole::callRun(ServerConsole* pConsole){
	pConsole->run();
}

void ServerConsole::start(){
	_thread = new std::thread(callRun, this);
}

void ServerConsole::stop(){
	_onRun = false;
}

void ServerConsole::title(){
	std::cout << prinmenuL << "\n" << prinmenuS << "\n" << prinmenuT << "\n" << prinmenu1 << "\n";
	std::cout << prinmenu2 << "\n" << prinmenu3 << "\n" << prinmenu4 << "\n" << prinmenu5 << "\n";
	std::cout << prinmenu6 << "\n" << prinmenu7 << "\n" << prinmenu8 << "\n" << prinmenu9 << "\n";
	std::cout << prinmenuS << "\n" << prinmenuL << "\n";
}

void ServerConsole::createDiskGroup()
{

}

void ServerConsole::run()
{	
	
}

