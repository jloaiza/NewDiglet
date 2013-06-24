#include "clientconsole.h"

ClientConsole::ClientConsole()
{
    initscr();
    nodelay(stdscr,0);
    getmaxyx(stdscr,_maxHeight, _maxWidth);
    activateColors();
    bkgd(COLOR_PAIR(1));
    principalScreen();
    refresh();
}

void ClientConsole::activateColors()
{
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLACK);
    init_pair(2,COLOR_BLUE,COLOR_BLACK);
}

void ClientConsole::principalScreen()
{
    clear();
    move(0,0);
    printw("1) LOGIN");
    move(1,0);
    printw("2) SIGN UP");
    move(2,0);
    printw("3) CONFIG");
    move(3,0);
    printw("4) EXIT");
    move(4,0);
    printw("Digite su opcion (1, 2, 3 o 4): ");
    char opcion[10];
    getstr(opcion);
    if(std::string(opcion) == "1")
    {
        login();
    }
    else if(std::string(opcion) == "2")
    {
        signUp();
    }
    else if(std::string(opcion) == "3")
    {
        config();
        principalScreen();
    }
    else if(std::string(opcion) == "4")
    {
        exit(0);
    }
    else
    {
        clear();
        principalScreen();
    }
}

void ClientConsole::login()
{
    clear();
    nocbreak();
    move(0,0);
    char user[200];
    char pass[200];
    char diskid[200];
    printw("RAIDB Login: ");
    echo();
    getstr(user);
    move(1,0);
    printw("Disk ID: ");
    getstr(diskid);
    move(2,0);
    printw("Password: ");
    noecho();
    getstr(pass);
    std::string securitykey = md5(std::string(pass));
    std::string exitmessage = std::string("connect ") + std::string(user) + std::string(" ") + std::string(securitykey) + std::string(diskid);
    std::string answermessage = sendMessage(exitmessage);
    if(!(answermessage[0] == '*'))
    {
        loadConsole(std::string(user));
    }
    else
    {
        login();
    }
}

void ClientConsole::signUp()
{
    clear();
    char login[200];
    char pass[200];
    char diskid[200];
    move(0,0);
    printw("Digite el nombre de usuario que desea utilizar: ");
    echo();
    getstr(login);
    move(1,0);
    printw("Digite el password que desea utilizar: ");
    noecho();
    getstr(pass);
    move(2,0);
    printw("Digite el ID del disco al que desea conectarse: ");
    echo();
    getstr(diskid);
    std::string securitykey = md5(std::string(pass));
    std::string exitmessage = std::string("adduser ") + std::string(login) + std::string(" ") + std::string(securitykey) + std::string(diskid);
    addUser(exitmessage);
    move(3,0);
    printw("Usuario agregado con exito.");
    loadConsole(std::string(login));
}
void ClientConsole::config()
{
    clear();
    echo();
    move(0,0);
    char ip[50];
    char port[10];
    printw("Digite la IP donde desea conectar: ");
    getstr(ip);
    move(1,0);
    printw("Digite el puerto por el cual desea conectar: ");
    getstr(port);
    _ip = std::string(ip);
    _port = atoi(std::string(port).c_str());
}

void ClientConsole::loadConsole(std::string pUsuario)
{
    clear();
    cbreak();
    move(0,0);
    echo();
    std::string console = std::string("RAIDB@") + std::string(pUsuario) + std::string(":") + std::string("/$ ");
    std::string message = " ";
    while(message != "disconnect")
    {
        clear();
        move(0,0);
        attron(COLOR_PAIR(2));
        printw(console.c_str());
        attroff(COLOR_PAIR(2));
        char messageo[200];
        attron(COLOR_PAIR(1));
        getstr(messageo);
        message = std::string(messageo);
        std::string respuesta = sendMessage(message);
        move(1,0);
        printw(respuesta.c_str());
        attroff(COLOR_PAIR(1));
        getch();
    }
    clear();
    move(0,0);
    principalScreen();
}

std::string ClientConsole::sendMessage(std::string pMessage)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    client->sendMessage(pMessage);
    std::string messagea =  client->readMessage();
    delete client;
    return messagea;
}

void ClientConsole::addUser(std::string pMessage)
{
    Client* client = new Client(_ip,_port);
    client->Connect();
    client->sendMessage(pMessage);
    delete client;
}