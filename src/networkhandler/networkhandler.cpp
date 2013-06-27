#include "networkhandler.h"

NetworkHandler::NetworkHandler()
{
    _sizeAddr = 0;
    _run = 1;
    _indicatorMessage = 0;
    _serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    _serverIP.sin_family = AF_INET ;
    _serverIP.sin_port = htons(PORT);
    _serverIP.sin_addr.s_addr = INADDR_ANY ;
    _sizeAddr = sizeof(struct sockaddr_in);
}

int NetworkHandler::meetClient(int pSocket)
{
    _runClient = 0; /* Verificador del ciclo. */   
    _exitCode = 0; /* Código de salida por defecto */         

    while (!_runClient)
    {
        /* Setear el buffer a cero. */
        memset(_inBuffer, 0, BUFFERSIZE);
        /* Recivimos la información y al mismo tiempo evaluamos si llego correctamente. */
        if ((_byteCount = recv(pSocket, _inBuffer, BUFFERSIZE, 0))== -1)
        {
            Error(5, "No se pudo recibir la información.");
        }
        if(_byteCount == 0)
        {
            std::cout << "!ATENCIÓN! El cliente " << inet_ntoa(_clientIP.sin_addr) <<  " se ha desconectado inesperadamente, conexión perdida." << std::endl;
            _runClient = 1;
        }
        /* Se convierte el _inBuffer de char a string para un manejo más fácil. */
        std::string inMessageBuffer = _inBuffer;

        /* Se envia el mensaje a otro método para su posterior evaluación. */
        inMessage(inMessageBuffer, pSocket);
    }
    close(pSocket); /* Se cierra la conexión del cliente. */
    return _exitCode; /* Retorna el codigo de salida */
}

void NetworkHandler::outMessage(std::string pMessage, int pSocket)
{
    const char *pMessageOut = pMessage.c_str();
    memset(_inBuffer, 0, BUFFERSIZE);
    sprintf(_inBuffer, pMessageOut); 
    if((_byteCount = send(pSocket, _inBuffer, strlen(_inBuffer), 0))== -1)
    {
        Error(6, "No se pudo enviar la información.");
    }
}

void NetworkHandler::Error(int pCode, std::string pSpecification)
{
    std::cout << "Error con codigo: " << pCode << " | " << " Especificación: " << pSpecification << std::endl;
    exit(1);
}

void NetworkHandler::WaitConnectionMsg(int pLoop)
{
    if (pLoop == 0)
    {
        std::cout << "[SERVER] Esperando conexión: " << std::endl;
        _indicatorMessage++;
    }
}

void NetworkHandler::verifyLiftErrors()
{
    if (_serverSocket == -1)
    {
        Error(1, "No se puede inicializar el socket.");
    }
    
    if (bind( _serverSocket, (struct sockaddr*) &_serverIP, sizeof(_serverIP) ) == -1)
    {
        Error(2, "El puerto está en uso."); 
    }

    if (listen( _serverSocket, 10) == -1 )
    {
        Error(3, "No se puede escuchar en el puerto especificado, ya está siendo usado");
    } 
}

void NetworkHandler::verifyNewClient()
{
    /* Se tiene que verificar si la conexión entrante es valida. */
    if (select(_serverSocket+1, &_rfds, NULL, NULL, &_timeAccept))
    {
        /* Si es valida se verifica si puede ser aceptada. */
        if ((_clientSocket = accept( _serverSocket, (struct sockaddr*)&_clientIP, &_sizeAddr))!= -1)
        {
            /* Se reinicia el mensaje de esperando conexión. */
            _indicatorMessage = 0; 
            /* Se imprime un mensaje de confirmación. */
            std::cout << "Se ha conectado la IP: " << inet_ntoa(_clientIP.sin_addr) << " por el puerto: " << _clientIP.sin_port << std::endl;
            switch ( _childPid = fork() )
            {
                case -1:  
                    /* Error al crear el nuevo cliente.*/
                    Error(4, "No se puede crear un nuevo cliente.");
                    break;
                case 0:   
                    /* Somos un nuevo cliente. */                           
                    _exit = meetClient(_clientSocket);
                    /* Se libera el cliente. */
                    exit(_exit); 
                default:  
                    /* Se libera el socket del cliente, ya que del mismo se encarga el hilo creado.*/ 
                    close(_clientSocket); 
                    break;
            }
        }
        else
        {
            std::cout << "Error al aceptar la conexión, reintentelo." << std::endl;
        }
    } 
}

void NetworkHandler::verifyDeadClient()
{
    /* Miramos si se ha cerrado algún cliente últimamente. */
    
    _childPid = waitpid(0, &_pidStatus, WNOHANG);
    
    if (_childPid > 0)
    {  
        if (WIFEXITED(_pidStatus))
        {
            std::cout << "Se ha desconectado el cliente: " << inet_ntoa(_clientIP.sin_addr) << std::endl;
            if ( WEXITSTATUS(_pidStatus) == 99)
            {
                /* Se ha pedido el cierre del servidor por parte del usuario. */
                std::cout << "Se ha pedido el cierre del servidor por parte de algun usuario." << std::endl;
                _run = 0;
            }
        }
        /* Se reinicia el mensaje de esperando conexión */
        _indicatorMessage = 0;
    }  
}

std::string NetworkHandler::getClientIP()
{
    return inet_ntoa(_clientIP.sin_addr);
}

void NetworkHandler::disconnectClient()
{
    _runClient = 1;
}

void NetworkHandler::closeServer()
{
    _runClient = 1;
    _exitCode = 99;
    _run = false;
}

void NetworkHandler::Run()
{  
    /* Se verifican los errores principales antes de levantar el servidor. */
    verifyLiftErrors();
    
    while(_run)
    {
        /* Imprime que se esta esperando alguna conexión. */
        
        WaitConnectionMsg(_indicatorMessage);
        
        /* Se carga el valor de rfdsn (Utilizados para la conexión) */
        
        FD_ZERO(&_rfds);
        FD_SET(_serverSocket, &_rfds);

        /* Se carga el valor de time. */        
        _timeAccept.tv_sec = 0;
        
        /* Se carga el valor del tiempo de espera */
        
        _timeAccept.tv_usec = 500000;  
        
        /* Se verifica si hay alguna conexión (Cliente) nueva. */
        
        verifyNewClient();
        
        /* Se verifica si alguna conexión (Cliente) murio. */
        
        verifyDeadClient();   
    }
    
    /* Se cierra el socket del servidor. */
    close(_serverSocket);
}

void NetworkHandler::callRun(NetworkHandler* pHandler)
{
    pHandler->Run();
}

void NetworkHandler::start()
{
    _thread = new std::thread(callRun, this);
}

std::thread* NetworkHandler::getThread()
{
    return _thread;
}


