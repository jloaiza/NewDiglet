#include "user.h"

bool User::operator==(std::string& pUser){
	return _name == pUser;
}

bool User::operator!=(std::string& pUser){
	return _name != pUser;
}

bool User::operator>(std::string& pUser){
	return _name > pUser;
}

bool User::operator>=(std::string& pUser){
	return _name >= pUser;
}

bool User::operator<(std::string& pUser){
	return _name < pUser;
}

bool User::operator<=(std::string& pUser){
	return _name <= pUser;
}


bool User::operator==(User& pUser){
	return _name == pUser.getName();
}

bool User::operator!=(User& pUser){
	return _name != pUser.getName();
}

bool User::operator>(User& pUser){
	return _name > pUser.getName();
}

bool User::operator>=(User& pUser){
	return _name >= pUser.getName();
}

bool User::operator<(User& pUser){
	return _name < pUser.getName();
}

bool User::operator<=(User& pUser){
	return _name <= pUser.getName();
}