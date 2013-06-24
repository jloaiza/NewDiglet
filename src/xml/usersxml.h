#ifndef USERXML
#define USERXML

#include "parserxml.h"

class usersxml
{
public:
	static void createXMLFile(std::string pDocumentDirection);
	static void addUser(std::string pDocumentDirection);
	static void addUserAttribute(std::string pDocumentDirection, int pUserIndex, std::string pUserAttribute, std::string pValue);
	static void addSecurityKey(std::string pDocumentDirection, int pUserIndex, std::string pSecurityKey);
	static std::string getSecurityKey(std::string pDocumentDirection, int pUserIndex);
	static std::string getIdUser(std::string pDocumentDirection, int pUserIndex);
	static std::string getUserDates(std::string pDocumentDirection, int pUserIndex);
};


#endif /* USERXML */