#include "lssconsole.h"
#include "info.h"
#include "../md5/md5.h"

#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

void echo(bool pON);

void LssConsole::start(){
	_thread = new std::thread(callRun, this);
}

void LssConsole::stop(){
	_onRun = false;
}

void LssConsole::callRun(LssConsole* pConsole){
	pConsole->run();
}

void echo(bool pON){
	struct termios t;
	tcgetattr(STDIN_FILENO, &t);
	if (pON){
		t.c_lflag |= ECHO;
	} else {
		t.c_lflag &= ~ECHO;
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void LssConsole::run(){
	title();	
	std::cout << std::endl;
	while (_onRun)
	{
		int clave = 0;
		std::cout << ">> ";
		std::cin >> clave;
		
		try
		{
			if (clave == 1)
			{
				int fileSize;
				std::cout << SIZE1;
				std::cin >> fileSize;

				std::cout << PASS;
				std::string secKey;
				echo(false);
				std::cin >> secKey;
				std::cout << std::endl;
				echo(true);
				secKey = md5(secKey);
				std::cout<<secKey<<std::endl;

				_diskManager->createDisk(fileSize, secKey);
			}
		 
			else if (clave == 2)
			{
				short fileName;
				std::cout << NAME;
				std::cin >> fileName;

				std::cout << PASS;
				std::string secKey;
				echo(false);
				std::cin >> secKey;
				std::cout << std::endl;
				echo(true);
				secKey = md5(secKey);

				std::cout<<std::endl;

				_diskManager->eraseDisk(fileName, secKey);
			}
			
			else if (clave == 3)
			{
				_diskManager->showDisks();
			}
		
			else if (clave == 4)
			{
				_diskManager->saveDisks();
			}
		
			else if (clave == 5)
			{
				_diskManager->stopSystem();
			}
			
			else
			{
				title();
			}
		}
		catch(int e)
		{
			title();
		}
		
	}
}

void LssConsole::title(){
	std::cout << lssmenuL << "\n" << lssmenuS << "\n" << lssmenu3 << "\n" << lssmenu4 << "\n";
	std::cout << lssmenu5 << "\n" << lssmenu6 << "\n" << lssmenu7 << "\n";
	std::cout << lssmenu8 << "\n" << lssmenuS << "\n" << lssmenuL << "\n";
}
