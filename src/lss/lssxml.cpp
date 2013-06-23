#include "lssxml.h"

void lssxml::createXMLFile(std::string pDocumentDirection)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->createDocument(pDocumentDirection);
	XMLParser->createRoot("disks");
	delete XMLParser;
}

void lssxml::addDisk(std::string pDocumentDirection)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	XMLParser->createRootChild("disk");
	delete XMLParser;
}

void lssxml::addDiskAttribute(std::string pDocumentDirection, int pDiskIndex, std::string pDiskAttribute, std::string pValue)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pDiskIndex;
	std::string diskdirection = "disks/disk[" + std::string(indexstream.str()) + "]/";
	XMLParser->createAttribute(diskdirection,pDiskAttribute, pValue);
	delete XMLParser;
}

void lssxml::addSecurityKey(std::string pDocumentDirection, int pDiskIndex, std::string pSecurityKey)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pDiskIndex;
	std::string diskdirection = "disks/disk[" + std::string(indexstream.str()) + "]/";
	XMLParser->createOtherChild(diskdirection, "secKey");
	std::string keydirection = std::string(diskdirection) + std::string("secKey/");
	XMLParser->createValue(keydirection, pSecurityKey);
	delete XMLParser;
}

std::string lssxml::getSecurityKey(std::string pDocumentDirection, int pDiskIndex)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pDiskIndex;
	std::string diskkeydirection = "/disks/disk[" + std::string(indexstream.str()) + "]/secKey/string()";
	std::string value = XMLParser->getAnyValue(diskkeydirection);
	delete XMLParser;
	return value;
}

std::string lssxml::getIdDisk(std::string pDocumentDirection, int pDiskIndex)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pDiskIndex;
	std::string diskattributedirection = "/disks/disk[" + std::string(indexstream.str()) + "]/@id/data(.)";
	std::string value = XMLParser->getAnyValue(diskattributedirection);
	delete XMLParser;
	return value;
}

std::string lssxml::getClientDisk(std::string pDocumentDirection, int pDiskIndex)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pDiskIndex;
	std::string diskattributedirection = "/disks/disk[" + std::string(indexstream.str()) + "]/@client/data(.)";
	std::string value = XMLParser->getAnyValue(diskattributedirection);
	delete XMLParser;
	return value;
}

std::string lssxml::getDiskDates(std::string pDocumentDirection, int pDiskIndex)
{
	std::string diskdates = getSecurityKey(pDocumentDirection, pDiskIndex) + ":" + getIdDisk(pDocumentDirection,pDiskIndex);
	return diskdates;
}