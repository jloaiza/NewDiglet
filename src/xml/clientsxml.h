#include "parserxml.h"

class clientsxml
{
public:
	static void createXMLFile(std::string pDocumentDirection);
	static void addClient(std::string pDocumentDirection);
	static void addClientAttribute(std::string pDocumentDirection, int pClientIndex, std::string pClientAttribute, std::string pValue);
	static std::string getClientIp(std::string pDocumentDirection, int pClientIndex);
	static std::string getClientPort(std::string pDocumentDirection, int pClientIndex);
	static std::string getClientDates(std::string pDocumentDirection, int pClientIndex);
};
