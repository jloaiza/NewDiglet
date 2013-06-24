#include "lssnetworkhandler.h"
#include "lssoperations.h"
#include "../tokenizer/tokenizer.h"

#include <exception>
#include <cstdlib>


void LSSNetworkHandler::inMessage(std::string pMessage, int pSocket){
	std::string command = Tokenizer::getCommandSpace(pMessage, 1);
	std::string param = Tokenizer::getParameters(pMessage);

	if (command == "connect"){
		connect(pSocket, param);

	} else if (command == "getFreeBlock"){
		getFreeBlock(pSocket, param);

	} else if (command == "readBlock"){
		readBlock(pSocket, param);

	} else if (command == "writeBlock"){
		writeBlock(pSocket, param);

	} else if (command == "getLssList"){
		getLssList(pSocket);
	
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
		short diskID = stoi(Tokenizer::getCommandSpace(pParam, 1));
		std::string secKey = Tokenizer::getCommandSpace(pParam, 2);
		if (secKey == ""){
			outMessage("?Error: El comando 'connect' espera dos atributos\n", pSocket);
		} else {
			outMessage(LssOperations::connect(diskID, secKey, _lssList, _manager), pSocket);
		}
	} catch (std::exception e){
		outMessage("?Error: El primer paremetro debe ser un número\n", pSocket);
	}
}

void LSSNetworkHandler::getFreeBlock(int pSocket, std::string pParam){
	try {
		short diskID = stoi(Tokenizer::getCommandSpace(pParam, 1));
		
		outMessage(LssOperations::getFreeBlock(diskID, _lssList), pSocket);

	} catch (std::exception e){
		outMessage("?Error: Error de tipo, algunos parametros debe ser números\n", pSocket);
	}
}

void LSSNetworkHandler::readBlock(int pSocket, std::string pParam){
	try {
		short diskID = stoi(Tokenizer::getCommandSpace(pParam, 1));
		int block = stoi(Tokenizer::getCommandSpace(pParam, 2));

		outMessage(LssOperations::readBlock(diskID, block, _lssList), pSocket);

	} catch (std::exception e){
		outMessage("?Error: Error de tipo, algunos parametros debe ser números\n", pSocket);
	}
}

void LSSNetworkHandler::writeBlock(int pSocket, std::string pParam){
	try {
		short diskID = stoi(Tokenizer::getCommandSpace(pParam, 1));
		int block = stoi(Tokenizer::getCommandSpace(pParam, 2));
		std::string data = Tokenizer::getCommandSpace(pParam, 3);
		if (data == ""){
			outMessage("?Error: El comando 'writeBlock' espera tres atributos\n", pSocket);
		} else {
			outMessage(LssOperations::writeBlock(diskID, block, data, _lssList), pSocket);
		}
	} catch (std::exception e){
		outMessage("?Error: El primer paremetro debe ser un número\n", pSocket);
	}
}

void LSSNetworkHandler::getLssList(int pSocket){
	
	outMessage(LssOperations::getLssList(_manager), pSocket);
	
}

void LSSNetworkHandler::getSize(int pSocket, std::string pParam){
	try {
		short diskID = stoi(Tokenizer::getCommandSpace(pParam, 1));
		outMessage(LssOperations::getSize(diskID, _manager), pSocket);

	} catch (std::exception e){
		outMessage("?Error: El paremetro debe ser un número\n", pSocket);
	}
}

void LSSNetworkHandler::writeBytes(int pSocket, std::string pParam){
	try {
		short diskID = stoi(Tokenizer::getCommandSpace(pParam, 1));
		int block = stoi(Tokenizer::getCommandSpace(pParam, 2));
		int offset = stoi(Tokenizer::getCommandSpace(pParam, 3));
		int size = stoi(Tokenizer::getCommandSpace(pParam, 4));
		std::string data = Tokenizer::getCommandSpace(pParam, 5);
		if (data == ""){
			outMessage("?Error: El comando 'writeBytes' espera cuatro atributos\n", pSocket);
		} else {
			outMessage(LssOperations::writeBytes(diskID, block, offset, size, data, _lssList), pSocket);
		}
	} catch (std::exception e){
		outMessage("?Error: Error de tipo, algunos parametros debe ser números\n", pSocket);
	}
}

void LSSNetworkHandler::readBytes(int pSocket, std::string pParam){
	try {

		short diskID = stoi(Tokenizer::getCommandSpace(pParam, 1));
		int block = stoi(Tokenizer::getCommandSpace(pParam, 2));
		int offset = stoi(Tokenizer::getCommandSpace(pParam, 3));
		int size = stoi(Tokenizer::getCommandSpace(pParam, 4));

		outMessage(LssOperations::readBytes(diskID, block, offset, size, _lssList), pSocket);

	} catch (std::exception e){
		outMessage("?Error: Error de tipo, algunos parametros debe ser números\n", pSocket);
	}
}

void LSSNetworkHandler::defaultCase(int pSocket, std::string pCommand){
	outMessage("?Error: El el comando '" + pCommand + "' no fue encontrado\n", pSocket);
}
