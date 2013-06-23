#include "diskgroupsxml.h"

void diskgroupsxml::createXMLFile(std::string pDocumentDirection)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->createDocument(pDocumentDirection);
	XMLParser->createRoot("diskgroups");
	delete XMLParser;
}

void diskgroupsxml::addDiskGroup(std::string pDocumentDirection)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	XMLParser->createRootChild("diskgroup");
	delete XMLParser;
}

void diskgroupsxml::addDiskGroupAttribute(std::string pDocumentDirection, int pDiskGroupIndex, std::string pDiskGroupAttribute, std::string pValue)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pDiskGroupIndex;
	std::string diskgroupdirection = "diskgroups/diskgroup[" + std::string(indexstream.str()) + "]/";
	XMLParser->createAttribute(diskgroupdirection,pDiskGroupAttribute, pValue);
	delete XMLParser;
}

void diskgroupsxml::addDiskGroupDisk(std::string pDocumentDirection, int pDiskGroupIndex)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pDiskGroupIndex;
	std::string diskgroupdirection = "diskgroups/diskgroup[" + std::string(indexstream.str()) + "]/";
	XMLParser->createOtherChild(diskgroupdirection,"disk");
	delete XMLParser;
}

void diskgroupsxml::addDiskGroupDiskAttribute(std::string pDocumentDirection, int pDiskGroupIndex, int pDiskGroupDiskIndex, std::string pDiskGroupDiskAttribute, std::string pValue)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream1;
	std::stringstream indexstream2;
	indexstream1 << pDiskGroupIndex;
	indexstream2 << pDiskGroupDiskIndex;
	std::string diskgroupdiskdirection = "diskgroups/diskgroup[" + std::string(indexstream1.str()) + "]/" + "disk[" + std::string(indexstream2.str()) + "]/";
	XMLParser->createAttribute(diskgroupdiskdirection, pDiskGroupDiskAttribute, pValue);
	delete XMLParser;
}

std::string diskgroupsxml::getDiskGroupId(std::string pDocumentDirection, int pDiskGroupIndex)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pDiskGroupIndex;
	std::string diskgroupdirection = "/diskgroups/diskgroup[" + std::string(indexstream.str()) + "]/@id/data(.)";
	std::string value = XMLParser->getAnyValue(diskgroupdirection);
	delete XMLParser;
	return value;
}

std::string diskgroupsxml::getDiskGroupBlockSize(std::string pDocumentDirection, int pDiskGroupIndex)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pDiskGroupIndex;
	std::string diskgroupdirection = "/diskgroups/diskgroup[" + std::string(indexstream.str()) + "]/@blocksize/data(.)";
	std::string value = XMLParser->getAnyValue(diskgroupdirection);
	delete XMLParser;
	return value;
}

std::string diskgroupsxml::getDiskGroupMaxSize(std::string pDocumentDirection, int pDiskGroupIndex)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pDiskGroupIndex;
	std::string diskgroupdirection = "/diskgroups/diskgroup[" + std::string(indexstream.str()) + "]/@maxsize/data(.)";
	std::string value = XMLParser->getAnyValue(diskgroupdirection);
	delete XMLParser;
	return value;
}

std::string diskgroupsxml::getDiskGroupRaid(std::string pDocumentDirection, int pDiskGroupIndex)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pDiskGroupIndex;
	std::string diskgroupdirection = "/diskgroups/diskgroup[" + std::string(indexstream.str()) + "]/@raid/data(.)";
	std::string value = XMLParser->getAnyValue(diskgroupdirection);
	delete XMLParser;
	return value;
}

std::string diskgroupsxml::getDiskGroupFunctional(std::string pDocumentDirection, int pDiskGroupIndex)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pDiskGroupIndex;
	std::string diskgroupdirection = "/diskgroups/diskgroup[" + std::string(indexstream.str()) + "]/@functional/data(.)";
	std::string value = XMLParser->getAnyValue(diskgroupdirection);
	delete XMLParser;
	return value;
}

std::string diskgroupsxml::getDiskGroupWorking(std::string pDocumentDirection, int pDiskGroupIndex)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream;
	indexstream << pDiskGroupIndex;
	std::string diskgroupdirection = "/diskgroups/diskgroup[" + std::string(indexstream.str()) + "]/@working/data(.)";
	std::string value = XMLParser->getAnyValue(diskgroupdirection);
	delete XMLParser;
	return value;
}

std::string diskgroupsxml::getDiskGroupDates(std::string pDocumentDirection, int pDiskGroupIndex)
{
	std::string value = getDiskGroupId(pDocumentDirection, pDiskGroupIndex) + ":" + getDiskGroupBlockSize(pDocumentDirection, pDiskGroupIndex) + ":" + getDiskGroupMaxSize(pDocumentDirection, pDiskGroupIndex) + ":" + getDiskGroupRaid(pDocumentDirection, pDiskGroupIndex) + ":" + getDiskGroupFunctional(pDocumentDirection, pDiskGroupIndex) + ":" + getDiskGroupWorking(pDocumentDirection, pDiskGroupIndex);
	return value;
}

std::string diskgroupsxml::getDiskGroupDiskId(std::string pDocumentDirection, int pDiskGroupIndex, int pDiskGroupDiskIndex)
{
	parserxml* XMLParser = new parserxml();
	XMLParser->loadDocument(pDocumentDirection);
	std::stringstream indexstream1;
	std::stringstream indexstream2;
	indexstream1 << pDiskGroupIndex;
	indexstream2 << pDiskGroupDiskIndex;
	std::string diskgroupdiskdirection = "/diskgroups/diskgroup[" + std::string(indexstream1.str()) + "]/disk[" + std::string(indexstream2.str()) + "]/" + "@id/data(.)";
	std::string value = XMLParser->getAnyValue(diskgroupdiskdirection);
	delete XMLParser;
	return value;	
}