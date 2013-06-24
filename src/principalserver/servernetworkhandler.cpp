
#include "servernetworkhandler.h"
#include "serveroperations.h"
#include "../tokenizer/tokenizer.h"
#include "../include/constants.h"
#include <exception>

#include <iostream>

void ServerNetworkHandler::inMessage(std::string pMessage, int pSocket){
	pMessage = Tokenizer::cleanEntry(pMessage);
	std::string command = Tokenizer::getCommandSpace(pMessage, 1);
	if (_sessionID == -1 && command != "connect" && command != "adduser" && command != "close"){
		outMessage("?Error: No se ha inciado sesión\n", pSocket);
	} else {
		std::string param = Tokenizer::getParameters(pMessage);
		std::cout<<param<<std::endl;
		if (command == "get"){
			get(param, pSocket);

		} else if (command == "cd"){
			cd(param, pSocket);
		
		} else if (command == "rm"){
			rm(param, pSocket);

		} else if (command == "touch"){
			touch(param, pSocket);

		} else if (command == "connect"){
			connect(param, pSocket);

		} else if (command == "mkdir"){
			mkdir(param, pSocket);

		} else if (command == "adduser"){
			adduser(param, pSocket);

		} else if (command == "openfile"){
			openfile(param, pSocket);

		} else if (command == "appendReg"){
			appendReg(param, pSocket);

		} else if (command == "delReg"){

			if (param == ""){
				delActualReg(pSocket);
			} else {
				delReg(param, pSocket);
			}
		
		} else if (command == "write"){
			write(param, pSocket);
		
		} else if (command == "seek"){
			seek(param, pSocket);
		
		} else if (command == "addReg"){
			addReg(param, pSocket);
		
		} else if (command == "read"){

			if (param == ""){
				readActual(pSocket);
			} else {
				readRegister(param, pSocket);
			}

		} else if (command == "close"){
			close(pSocket);
		} else if (command == "consoleMode"){
			consoleMode(param, pSocket);
		} else {
			outMessage("?Error: No se ha encontrado la instrucción " + command + '\n', pSocket);
		}
		consoleUI(pSocket);
	}
}

void ServerNetworkHandler::consoleMode(std::string pParameters, int pSocket){
	std::string param = Tokenizer::getCommandSpace(pParameters, 1);
	if (param == "false"){
		_consoleMode = false;
	} else if (param == "true"){
		_consoleMode = true;
	} else {
		outMessage("?Error: El comando 'consoleMode' espera un boolean true/false\n", pSocket);
	}
}

void ServerNetworkHandler::consoleUI(int pSocket){
	if (_consoleMode){
		std::string userInfo = ServerOperations::getInfo(_sessionID); //OBTENER PATH
		std::string currentPath = Tokenizer::getCommandSpace(userInfo, 1);
		std::string user = Tokenizer::getCommandSpace(userInfo, 2);
		std::string message = getClientIP() + std::string("@") + user + std::string(":~") + currentPath + std::string(">> ");
		outMessage(message, pSocket);
	}
}

void ServerNetworkHandler::outMessageValidate(std::string pMessage, int pSocket){
	if (pMessage != ""){
		outMessage(pMessage, pSocket);
	}
}

void ServerNetworkHandler::mkdir(std::string pParameters, int pSocket){
	if (pParameters == ""){
		outMessage("?Error: El comando 'get' espera un parametro\n", pSocket);
	} else {
		std::string name = Tokenizer::getCommandSpace(pParameters, 1);
		outMessageValidate(ServerOperations::mkdir(_sessionID, name), pSocket);
	}
}

void ServerNetworkHandler::get(std::string pParameters, int pSocket){
	if (pParameters == ""){
		outMessage("?Error: El comando 'get' espera un parametro\n", pSocket);
	} else {
		std::string path = Tokenizer::getCommandSpace(pParameters, 1);
		outMessageValidate(ServerOperations::get(_sessionID, path), pSocket);
	}
}

void ServerNetworkHandler::cd(std::string pParameters, int pSocket){
	if (pParameters == ""){
		outMessage("?Error: El comando 'cd' espera un parametro\n", pSocket);
	} else {
		std::string path = Tokenizer::getCommandSpace(pParameters, 1);
		outMessageValidate(ServerOperations::cd(_sessionID, path), pSocket);
	}
}

void ServerNetworkHandler::rm(std::string pParameters, int pSocket){
	if (pParameters == ""){
		outMessage("?Error: El comando 'rm' espera un parametro\n", pSocket);
	} else {
		std::string path = Tokenizer::getCommandSpace(pParameters, 1);
		outMessageValidate(ServerOperations::rm(_sessionID, path), pSocket);
	}
}

void ServerNetworkHandler::touch(std::string pParameters, int pSocket){
	std::string path = Tokenizer::getCommandSpace(pParameters, 1);
	std::string format = Tokenizer::getCommandSpace(pParameters, 3);

	if (format == ""){
		outMessage("?Error: El comando 'touch' espera tres parametros\n", pSocket);
	} else {
		outMessageValidate(ServerOperations::touch(_sessionID, path, format), pSocket);
	}

}

void ServerNetworkHandler::connect(std::string pParameters, int pSocket){
	std::string user = Tokenizer::getCommandSpace(pParameters, 1);
	std::string secKey = Tokenizer::getCommandSpace(pParameters, 2);
	std::string disk = Tokenizer::getCommandSpace(pParameters, 3);

	if (disk == ""){
		outMessage("*Error de implementación: El comando interno 'connect' espera tres parametros\n", pSocket);
	} else {
		_sessionID = ServerOperations::connect(user, secKey, disk);
		if (_sessionID == -1){
			outMessage("No se ha podido iniciar sesión, nombre de usuario, contraseña o disco incorrecto\n", pSocket);
		} 
	}

}

void ServerNetworkHandler::adduser(std::string pParameters, int pSocket){
	std::string user = Tokenizer::getCommandSpace(pParameters, 1);
	std::string secKey = Tokenizer::getCommandSpace(pParameters, 2);
	std::string disk = Tokenizer::getCommandSpace(pParameters, 3);

	if (disk == ""){
		outMessage("*Error de implementación: El comando interno 'adduser' espera tres parametros\n", pSocket);
	} else {
		_sessionID = ServerOperations::adduser(user, secKey, disk);
		if (_sessionID == -1){
			outMessage("Error de registro, el nombre de usuario ya existe o disco incorrecto\n", pSocket);
		}
	}
}

void ServerNetworkHandler::openfile(std::string pParameters, int pSocket){
	if (pParameters == ""){
		outMessage("?Error: El comando 'openfile' espera un parametro\n", pSocket);
	} else {
		std::string path = Tokenizer::getCommandSpace(pParameters, 1);
		outMessageValidate(ServerOperations::openfile(_sessionID, path), pSocket);
	}
}

void ServerNetworkHandler::appendReg(std::string pParameters, int pSocket){
	if (pParameters == ""){
		outMessage("?Error: El comando 'appendReg' espera un parametro\n", pSocket);
	} else {
		std::string data = Tokenizer::getCommandSpace(pParameters, 1);
		outMessageValidate(ServerOperations::appendReg(_sessionID, data), pSocket);
	}
}

void ServerNetworkHandler::delActualReg(int pSocket){
	outMessageValidate(ServerOperations::delReg(_sessionID, PS::SEEK_POS), pSocket);
}

void ServerNetworkHandler::delReg(std::string pParameters, int pSocket){
	try {
		int regNum = stoi( Tokenizer::getCommandSpace(pParameters, 1) );
		outMessageValidate(ServerOperations::delReg(_sessionID, regNum), pSocket);
	} catch (std::exception e){
		outMessage("?Error: Se esperaba un número\n", pSocket);
	}
}

void ServerNetworkHandler::write(std::string pParameters, int pSocket){
	if (pParameters == ""){
		outMessage("?Error: El comando 'write' espera al menos un parametro\n", pSocket);
	} else {
		std::string data = Tokenizer::getCommandSpace(pParameters, 1);

		if (Tokenizer::getCommandSpace(pParameters, 2) == ""){

			outMessageValidate(ServerOperations::write(_sessionID, data, PS::SEEK_POS), pSocket);

		} else {

			try {

				int regNum = stoi( Tokenizer::getCommandSpace(pParameters, 2) );
				outMessageValidate(ServerOperations::write(_sessionID, data, regNum), pSocket);

			} catch (std::exception e){
				outMessage("?Error: El segundo parametro de write debe ser un número\n", pSocket);
			}
		}
	}
}

void ServerNetworkHandler::seek(std::string pParameters, int pSocket){
	if (pParameters == ""){
		outMessage("?Error: El comando 'seek' espera un parametro\n", pSocket);
	} else {
		try {
			int seek = stoi( Tokenizer::getCommandSpace(pParameters, 1) );
			outMessageValidate(ServerOperations::moveSeek(_sessionID, seek), pSocket);
		} catch (std::exception& e) {
			outMessage("?Error: Se esperaba un número\n", pSocket);
		}
	}
}

void ServerNetworkHandler::addReg(std::string pParameters, int pSocket){
	if (pParameters == ""){
		outMessage("?Error: El comando 'addReg' espera un parametro\n", pSocket);
	} else {
		std::string data = Tokenizer::getCommandSpace(pParameters, 1);
		outMessageValidate(ServerOperations::write(_sessionID, data, PS::SEEK_POS), pSocket);
	}
}

void ServerNetworkHandler::readActual(int pSocket){
	outMessageValidate(ServerOperations::readReg(_sessionID, PS::SEEK_POS), pSocket);
}

void ServerNetworkHandler::readRegister(std::string pParameters, int pSocket){
	if (pParameters == ""){
		outMessage("?Error: El comando 'readRegister' espera un parametro\n", pSocket);
	} else {
		try {
				int regNum = stoi( Tokenizer::getCommandSpace(pParameters, 1) );
				outMessageValidate(ServerOperations::readReg(_sessionID, regNum), pSocket);
			} catch (std::exception e){
				outMessage("?Error: Se esperaba un número\n", pSocket);
			}
	}
}

void ServerNetworkHandler::close(int pSocket){
	outMessage(ServerOperations::close(&_sessionID), pSocket);
	if (_sessionID == -1){
		disconnectClient();
	}
}