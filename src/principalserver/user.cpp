#include "user.h"

bool User::operator==(std::string& pUser){
	return _name == pUser->getName();
}

bool User::operator!=(std::string& pUser){
	return _name != pUser->getName();
}

bool User::operator>(std::string& pUser){
	return _name > pUser->getName();
}

bool User::operator>=(std::string& pUser){
	return _name >= pUser->getName();
}

bool User::operator<(std::string& pUser){
	return _name < pUser->getName();
}

bool User::operator<=(std::string& pUser){
	return _name <= pUser->getName();
}