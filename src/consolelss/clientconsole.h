#ifndef CLIENTCONSOLE_H
#define	CLIENTCONSOLE_H

#include <ncurses.h>
#include <iostream>
#include <string>
#include "../md5/md5.h"
#include "../clientcpp/client.h"

class ClientConsole
{
public:
	ClientConsole();
private:
	std::string _ip;
	int _port;
	int _maxWidth;
	int _maxHeight;
	char _edge;
    void activateColors();
    void principalScreen();
    void login();
    void signUp();
    void config();
    void loadConsole(std::string pUsuario);
    std::string sendMessage(std::string pMessage);
    void addUser(std::string pMessage);
};

#endif	/* CLIENTCONSOLE_H */