#include "clientsxml.h"

void clientsxml::createXMLFile(std::string pDocumentDirection)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->createDocument(pDocumentDirection);
	XMLParser->createRoot("clients");
	delete XMLParser;
}

void clientsxml::addClient(std::string pDocumentDirection)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	XMLParser->createRootChild("client");
	delete XMLParser;
}

void clientsxml::addClientAttribute(std::string pDocumentDirection, int pClientIndex, std::string pClientAttribute, std::string pValue)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pClientIndex;
	std::string clientdirection = "clients/client[" + std::string(indexstream.str()) + "]/";
	XMLParser->createAttribute(clientdirection,pClientAttribute, pValue);
	delete XMLParser;
}

std::string clientsxml::getClientIp(std::string pDocumentDirection, int pClientIndex)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pClientIndex;
	std::string clientipdirection = "/clients/client[" + std::string(indexstream.str()) + "]/@ip/data(.)";
	std::string value = XMLParser->getAnyValue(clientipdirection);
	delete XMLParser;
	return value;
}

std::string clientsxml::getClientPort(std::string pDocumentDirection, int pClientIndex)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pClientIndex;
	std::string clientportdirection = "/clients/client[" + std::string(indexstream.str()) + "]/@port/data(.)";
	std::string value = XMLParser->getAnyValue(clientportdirection);
	delete XMLParser;
	return value;
}

std::string clientsxml::getClientDates(std::string pDocumentDirection, int pClientIndex)
{
	std::string clientdates = getClientIp(pDocumentDirection, pClientIndex) + ":" + getClientPort(pDocumentDirection, pClientIndex);
	return clientdates;
}