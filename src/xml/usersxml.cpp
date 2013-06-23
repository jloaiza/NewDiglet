#include "usersxml.h"

void usersxml::createXMLFile(std::string pDocumentDirection)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->createDocument(pDocumentDirection);
	XMLParser->createRoot("users");
	delete XMLParser;
}

void usersxml::addUser(std::string pDocumentDirection)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	XMLParser->createRootChild("user");
	delete XMLParser;
}

void usersxml::addUserAttribute(std::string pDocumentDirection, int pUserIndex, std::string pUserAttribute, std::string pValue)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pUserIndex;
	std::string userdirection = "users/user[" + std::string(indexstream.str()) + "]/";
	XMLParser->createAttribute(userdirection,pUserAttribute, pValue);
	delete XMLParser;
}

void usersxml::addSecurityKey(std::string pDocumentDirection, int pUserIndex, std::string pSecurityKey)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pUserIndex;
	std::string userdirection = "users/user[" + std::string(indexstream.str()) + "]/";
	XMLParser->createOtherChild(userdirection, "secKey");
	std::string keydirection = std::string(userdirection) + std::string("secKey/");
	XMLParser->createValue(keydirection, pSecurityKey);
	delete XMLParser;
}

std::string usersxml::getSecurityKey(std::string pDocumentDirection, int pUserIndex)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pUserIndex;
	std::string userkeydirection = "/users/user[" + std::string(indexstream.str()) + "]/secKey/string()";
	std::string value = XMLParser->getAnyValue(userkeydirection);
	delete XMLParser;
	return value;
}

std::string usersxml::getIdUser(std::string pDocumentDirection, int pUserIndex)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pUserIndex;
	std::string userattributedirection = "/users/user[" + std::string(indexstream.str()) + "]/@id/data(.)";
	std::string value = XMLParser->getAnyValue(userattributedirection);
	delete XMLParser;
	return value;
}

std::string usersxml::getUserDates(std::string pDocumentDirection, int pUserIndex)
{
	std::string userdates = getSecurityKey(pDocumentDirection, pUserIndex) + ":" + getIdUser(pDocumentDirection,pUserIndex);
	return userdates;
}