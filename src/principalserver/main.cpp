#include "generalmanager.h"
#include <qt4/QtGui/QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	GeneralManager* manager = new GeneralManager();
	manager->startSystem();
    return 0;
}

