
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

/* Tamaño del buffer. */

#define BUFFERSIZE 512

class Client 
{
    public:

        /**
        * Constructor de la clase, llama a los métodos para iniciar la conexión.
        * @param pIp: Ip a la cual se quiere conectar.
        * @param pPort: Puerto por el cual se quiere conectar.
        */
        Client(std::string pIp, int pPort);

        /**
        * Muestra errores que se puedan dar al realizar las conexiones.
        * @param pError: Recive la especificación del error.
        */
        void Error(std::string pError);

        /**
        * Método que se encarga de abrir el socket para poder trabajar con las conexiones.
        */
        void openSocket();

        /**
        * Método que se encarga de setear las variables principales del socket
        * para poder realizar uan conexión exitosa.
        */
        void setSocket();

        /**
        * Método que conecta hacia la IP dada al instanciar la clase junto con su puerto.
        */
        void Connect();

        /**
        * Se encarga de enviar un mensaje hacia la IP dada al construir la clase, 
        * llamese mensaje a un string con algúna instrucción.
        * @param pMessage: El comando o la instrucción a enviar por la red.
        */
        void sendMessage(std::string pMessage);

        /**
        * Método que se encarga de leer desde el socket todo lo recivido al enviar algún
        * comando por medio de la red, es decir, la respuesta del servidor.
        */
        std::string readMessage();
        /**
        * Método que devuelve true si el cliente está conectado al server o false si no lo está-
        */        
        bool isConnect();
    private:
        /* Getters y setters para el puerto y la IP. */
        void setPort(int _port){this->_port = _port;}
        int getPort() const{return _port;}
        void setIp(std::string _ip){this->_ip = _ip;}
        std::string getIp() const{return _ip;}
        
        /* Variables para el manejo de conexión de red dentro del protocolo.*/
        typedef struct sockaddr *_socketDirection;
        std::string _ip;
        int _port;
        int _socket;
        int cto;
        struct sockaddr_in _connection;
        char _inMessage[BUFFERSIZE];
};

