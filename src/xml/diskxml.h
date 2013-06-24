#ifndef DISKXML
#define DISKXML

#include "parserxml.h"

class DiskXML
{
public:
	static void createXMLFile(std::string pDocumentDirection);
	static void addDisk(std::string pDocumentDirection);
	static void addDiskAttribute(std::string pDocumentDirection, int pDiskIndex, std::string pDiskAttribute, std::string pValue);
	static void addSecurityKey(std::string pDocumentDirection, int pDiskIndex, std::string pSecurityKey);
	static std::string getSecurityKey(std::string pDocumentDirection, int pDiskIndex);
	static std::string getIdDisk(std::string pDocumentDirection, int pDiskIndex);
	static std::string getClientDisk(std::string pDocumentDirection, int pDiskIndex);
	static std::string getDiskDates(std::string pDocumentDirection, int pDiskIndex);
};

#endif /* DISKXML */