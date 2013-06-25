#include "lssnetworkhandler.h"
#include "lssoperations.h"
#include "../tokenizer/tokenizer.h"

#include <exception>
#include <cstdlib>

LSSNetworkHandler::LSSNetworkHandler(){
	
}

void LSSNetworkHandler::inMessage(std::string pMessage, int pSocket){
	std::string command = Tokenizer::getCommandSpace(pMessage, 1);
	std::string param = Tokenizer::getParameters(pMessage);

	if (command == "connect"){
		connect(pSocket, param);

	} else if (command == "startClient"){
		outMessage( std::to_string(LssOperations::newSession()) , pSocket);

	} else if (command == "readBlock"){
		readBlock(pSocket, param);

	} else if (command == "writeBlock"){
		writeBlock(pSocket, param);

	} else if (command == "getSize"){
		getSize(pSocket, param);
	
	} else if (command == "writeBytes"){
		writeBytes(pSocket, param);

	} else if (command == "readBytes"){
		readBytes(pSocket, param);

	} else {
		defaultCase(pSocket, command);

	}
}

void LSSNetworkHandler::connect(int pSocket, std::string pParam){
	try {

		int sessionID = stoi(Tokenizer::getCommandSpace(pParam, 1));
		short diskID = stoi(Tokenizer::getCommandSpace(pParam, 2));
		std::string secKey = Tokenizer::getCommandSpace(pParam, 3);
		if (secKey == ""){
			outMessage("?Error: El comando 'connect' espera dos atributos\n", pSocket);
		} else {
			outMessage(LssOperations::connect(diskID, secKey, sessionID), pSocket);
		}
	} catch (std::exception e){
		outMessage("?Error: El primer y segundo paremetro debe ser un número\n", pSocket);
	}
}

void LSSNetworkHandler::readBlock(int pSocket, std::string pParam){
	try {
		int sessionID = stoi(Tokenizer::getCommandSpace(pParam, 1));
		short diskID = stoi(Tokenizer::getCommandSpace(pParam, 2));
		int block = stoi(Tokenizer::getCommandSpace(pParam, 3));

		outMessage(LssOperations::readBlock(diskID, block, sessionID), pSocket);

	} catch (std::exception e){
		outMessage("?Error: Error de tipo, algunos parametros debe ser números\n", pSocket);
	}
}

void LSSNetworkHandler::writeBlock(int pSocket, std::string pParam){
	try {
		int sessionID = stoi(Tokenizer::getCommandSpace(pParam, 1));
		short diskID = stoi(Tokenizer::getCommandSpace(pParam, 2);
		std::string data = pParam.substr(pParam.find(' ')+1, pParam.length() - pParam.find(' '));
		if (data == ""){
			outMessage("?Error: El comando 'writeBlock' espera dos atributos\n", pSocket);
		} else {
			outMessage(LssOperations::writeBlock(diskID, data, sessionID), pSocket);
		}
	} catch (std::exception e){
		outMessage("?Error: El primer paremetro debe ser un número\n", pSocket);
	}
}

void LSSNetworkHandler::getSize(int pSocket, std::string pParam){
	try {
		int sessionID = stoi(Tokenizer::getCommandSpace(pParam, 1));
		short diskID = stoi(Tokenizer::getCommandSpace(pParam, 2));
		outMessage(LssOperations::getSize(diskID, sessionID), pSocket);

	} catch (std::exception e){
		outMessage("?Error: El paremetro debe ser un número\n", pSocket);
	}
}

void LSSNetworkHandler::writeBytes(int pSocket, std::string pParam){
	try {
		int sessionID = stoi(Tokenizer::getCommandSpace(pParam, 1));
		short diskID = stoi(Tokenizer::getCommandSpace(pParam, 2));
		int block = stoi(Tokenizer::getCommandSpace(pParam, 3));
		int offset = stoi(Tokenizer::getCommandSpace(pParam, 4));
		int size = stoi(Tokenizer::getCommandSpace(pParam, 5));
		std::string data = Tokenizer::getCommandSpace(pParam, 6);
		if (data == ""){
			outMessage("?Error: El comando 'writeBytes' espera cuatro atributos\n", pSocket);
		} else {
			outMessage(LssOperations::writeBytes(diskID, block, offset, size, data, sessionID), pSocket);
		}
	} catch (std::exception e){
		outMessage("?Error: Error de tipo, algunos parametros debe ser números\n", pSocket);
	}
}

void LSSNetworkHandler::readBytes(int pSocket, std::string pParam){
	try {
		int sessionID = stoi(Tokenizer::getCommandSpace(pParam, 1));
		short diskID = stoi(Tokenizer::getCommandSpace(pParam, 2));
		int block = stoi(Tokenizer::getCommandSpace(pParam, 3));
		int offset = stoi(Tokenizer::getCommandSpace(pParam, 4));
		int size = stoi(Tokenizer::getCommandSpace(pParam, 5));

		outMessage(LssOperations::readBytes(diskID, block, offset, size, sessionID), pSocket);

	} catch (std::exception e){
		outMessage("?Error: Error de tipo, algunos parametros debe ser números\n", pSocket);
	}
}

void LSSNetworkHandler::defaultCase(int pSocket, std::string pCommand){
	outMessage("?Error: El el comando '" + pCommand + "' no fue encontrado\n", pSocket);
}
