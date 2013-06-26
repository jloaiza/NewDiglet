#include "serverconsole.h"

#include <iostream>
#include <string>
#include "../md5/md5.h"
#include "generalmanager.h"
#include "../include/constants.h"
#include <termios.h>
#include "../tokenizer/tokenizer.h"

void echo(bool pON);
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

void ServerConsole::callRun(ServerConsole* pConsole){
	pConsole->run();
}

void ServerConsole::start(){
	_thread = new std::thread(callRun, this);
}

void ServerConsole::stop(){
	_onRun = false;
}

void ServerConsole::title(){
	std::cout << prinmenuL << "\n" << prinmenuW1 << "\n" << prinmenuW2 << "\n" << prinmenuS << "\n";
	std::cout << prinmenuT << "\n" << prinmenu1 << "\n";
	std::cout << prinmenu2 << "\n" << prinmenu3 << "\n" << prinmenu4 << "\n" << prinmenu5 << "\n";
	std::cout << prinmenu6 << "\n" << prinmenu7 << "\n" << prinmenu8 << "\n" << prinmenu9 << "\n";
	std::cout << prinmenuS << "\n" << prinmenuL << "\n";
}

void ServerConsole::addDisk(){
	//----------------------------------------------------------------
	std::cout<<"ID del DiskGroup al que desea agregar el disco: ";
	std::string idDiskGroup;

	std::cin>>idDiskGroup;
	idDiskGroup = Tokenizer::cleanEntry(idDiskGroup);

	std::cout<<std::endl;

	//----------------------------------------------------------------

	std::cout<<"Dirección IP del LSS: ";
	std::string ip;

	std::cin>>ip;
	ip = Tokenizer::cleanEntry(ip);

	std::cout<<std::endl;

	//----------------------------------------------------------------

	std::cout<<"Puerto del LSS: ";
	int port;
	std::cin>>port;
	std::cout<<std::endl;

	//----------------------------------------------------------------
	std::cout<<"ID del LSS: ";
	int id;
	std::cin>>id;
	std::cout<<std::endl;

	//----------------------------------------------------------------
	std::cout<<"SecurityKey del LSS: ";
	echo(false);
	std::string secKey;

	std::cin>>secKey;
	secKey = Tokenizer::cleanEntry(secKey);

	secKey = md5(secKey);
	echo(true);
	std::cout<<std::endl;

	_manager->addLSS(idDiskGroup, ip, port, id, secKey);
}

void ServerConsole::removeDisk(){
	std::cout<<"Not implemented yet."<<std::endl;
}

void ServerConsole::createDiskGroup(){
	std::cout<<"Tipos de RAID disponibles:  NO RAID = -1  ;  RAID 0 = 0  ;  RAID 1 = 1  ;  RAID 5 = 5"<<std::endl;
	std::cout<<"Tipo de RAID a implementar: ";
	int raid;
	std::cin>>raid;
	std::cout<<std::endl;

	std::cout<<"Tamaño de bloque: ";
	int blockSize;
	std::cin>>blockSize;
	std::cout<<std::endl;

	std::cout<<"Etiqueta del diskGroup: ";
	std::string id;
	std::cin>>id;
	std::cout<<std::endl;	

	_manager->defineDiskGroup(raid, blockSize, id);
}

void ServerConsole::removeDiskGroup(){
	std::cout<<"Not implemented yet."<<std::endl;
}

void ServerConsole::showDiskGroups(){
	std::cout<<_manager->getDiskGroups()<<std::endl;
}

void ServerConsole::showSpecificDiskGroup(){
	std::cout<<"Etiqueta del DiskGroup a mostrar: ";
	std::string id;
	std::cin>>id;
	std::cout<<_manager->getDiskGroupStatus(id)<<std::endl;	
}

void ServerConsole::startDiskGroup(){
	std::cout<<"Etiqueta del DiskGroup a iniciar: ";
	std::string id;
	std::cin>>id;
	_manager->startDiskGroup(id);
}

void ServerConsole::stopDiskGroup(){
	std::cout<<"Etiqueta del DiskGroup a detener: ";
	std::string id;
	std::cin>>id;
	_manager->stopDiskGroup(id);
}

void ServerConsole::exitSystem(){
	_manager->stopSystem();
}

void ServerConsole::run()
{	
	while (_onRun){
		title();
		std::cout<<">> ";
		int choice;
		std::cin>>choice;
		switch (choice){
			case PSC::ADD_DISK:
				addDisk();
				break;

			case PSC::ERASE_DISK:
				removeDisk();
				break;

			case PSC::CREATE_DISKGROUP:
				createDiskGroup();
				break;

			case PSC::ERASE_DISKGROUP:
				removeDiskGroup();
				break;

			case PSC::SHOW_DISKGROUPS:
				showDiskGroups();
				break;

			case PSC::SHOW_SPEC_DISKGROUP:
				showSpecificDiskGroup();
				break;

			case PSC::START_DISKGROUP:
				startDiskGroup();
				break;

			case PSC::STOP_DISKGROUP:
				stopDiskGroup();
				break;

			case PSC::EXIT:
				exitSystem();
				break;

			default:
				std::cout<<"Número de comando incorrecto."<<std::endl;

		}
	}
}

