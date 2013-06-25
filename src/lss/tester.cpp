#include <iostream>

#include "lss.h"
#include "lssmanager.h"


int main(int argc, char **argv)
{



	LssManager* manager = new LssManager();
	manager->startSystem();
	
	// manager->createDisk(1024, "er");
	// manager->createDisk(1024, "er");
	
	// std::string block1 = "$$$$$$$$$$$$";
	// std::string block2 = "%%%%%%%%%%%%";
	// std::string block3 = "&&&&&&&&&&&&";
	// std::string block4 = "~~~~~~~~~~~~";
	
	// manager->write(block1, 1, 0); 
	// short tmp =  manager->write(block2, 1, 0);
	// short tmp2 =  manager->write(block3, 1, 0);
	// manager->write(block4, 1, 0);
	
	// manager->eraseBlock(1, tmp);
	// manager->eraseBlock(1, tmp2);
	
	// manager->write(block2, 1, 0);
	
	return 0;
}




/** g++ -std=c++11 -pthread lss.cpp lssmanager.cpp lssoperations.cpp lssconsole.cpp lssnetworkhandler.cpp ../structures/simplelist/simplelist.cpp ../structures/simplelist/node.cpp ../tokenizer/tokenizer.cpp ../binaryoperations/baseconverter.cpp ../binaryoperations/byteshandler.cpp ../md5/md5.cpp ../networkhandler/networkhandler.cpp tester.cpp -o tester */
