#ifndef DISKGROUPSXML
#define DISKGROUPSXML

#include "parserxml.h"

class diskgroupsxml
{
public:
	static void createXMLFile(std::string pDocumentDirection);
	static void addDiskGroup(std::string pDocumentDirection);
	static void addDiskGroupAttribute(std::string pDocumentDirection, int pDiskGroupIndex, std::string pDiskGroupAttribute, std::string pValue);
	static void addDiskGroupDisk(std::string pDocumentDirection, int pDiskGroupIndex);
	static void addDiskGroupDiskAttribute(std::string pDocumentDirection, int pDiskGroupIndex, int pDiskGroupDiskIndex, std::string pDiskGroupDiskAttribute, std::string pValue);
	static std::string getDiskGroupId(std::string pDocumentDirection, int pDiskGroupIndex);
	static std::string getDiskGroupBlockSize(std::string pDocumentDirection, int pDiskGroupIndex);
	static std::string getDiskGroupMaxSize(std::string pDocumentDirection, int pDiskGroupIndex);
	static std::string getDiskGroupRaid(std::string pDocumentDirection, int pDiskGroupIndex);
	static std::string getDiskGroupFunctional(std::string pDocumentDirection, int pDiskGroupIndex);
	static std::string getDiskGroupWorking(std::string pDocumentDirection, int pDiskGroupIndex);
	static std::string getDiskGroupDates(std::string pDocumentDirection, int pDiskGroupIndex);
	static std::string getDiskGroupDiskId(std::string pDocumentDirection, int pDiskGroupIndex, int pDiskGroupDiskIndex);
};

#endif /* DISKGROUPSXML */