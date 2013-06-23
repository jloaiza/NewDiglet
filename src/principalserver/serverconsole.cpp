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
	std::cout << lssmenuL << "\n" << lssmenuS << "\n" << lssmenu3 << "\n" << lssmenu4 << "\n";
	std::cout << lssmenu5 << "\n" << lssmenu6 << "\n" << lssmenu7 << "\n" << lssmenu8 << "\n";
	std::cout << lssmenu9 << "\n" << lssmenuS << "\n" << lssmenuL << "\n";
}

void ServerConsole::createDiskGroup()
{
	std::cout << lssmenuL << "\n" << lssmenuS << "\n" << lssmenu3 << "\n" << lssmenu10 << "\n";
	std::cout << lssmenu11 << "\n" << lssmenuS << "\n" << lssmenuL << "\n";
}

void ServerConsole::run()
{	
	title();
	
	while (true)
	{
		int clave = 0;
		std::cin >> clave;
		
		if (clave == 1)
		{
			while (true)
			{
				int clave2 = 0;
				createDiskGroup();
				std::cin >> clave2;
				if (clave2 == 1)
				{
					char * diskID;
					std::cout << DISKID;
					std::cin >> diskID;
					std::cout << "agregar " << diskID << std::endl;
				}
				else if (clave2==2)
				{
					break;
				}
				else if (clave2 >= 3)
				{
					createDiskGroup();
				}
			}
			/*	
			}
			int fileSize;
			std::cout << SIZE1;
			std::cin >> fileSize;

			std::cout << PASS;
			std::string secKey;
			echo(false);
			std::cin >> secKey;
			echo(true);
			secKey = md5(secKey);

			std::cout<<secKey<<std::endl;

			_diskManager->createDisk(fileSize, secKey);
			*/
		}
		 
		else if (clave == 2)
		{
			/*
			short fileName;
			std::cout << NAME;
			std::cin >> fileName;

			std::cout << PASS;
			std::string secKey;
			echo(false);
			std::cin >> secKey;
			echo(true);
			secKey = md5(secKey);

			std::cout<<std::endl;

			_diskManager->eraseDisk(fileName, secKey);
			*/
		}
		
		else if (clave == 3)
		{
			//_diskManager->showDisks();
		}
				
		else if (clave == 4)
		{
			//_diskManager->saveDisks();
		}
		
		else if (clave == 5)
		{
			/*
			char * fileName;
			std::cout << NAME2;
			std::cin >> fileName;
			//_diskManager->loadDisks();
			*/
		}
		
		else if (clave == 6)
		{
			break;
		}
		
		else if (clave >= 7)
		{
			title();
		}
	}
	return 0;
}

