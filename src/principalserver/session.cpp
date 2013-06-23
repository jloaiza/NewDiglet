#include "session.h"

int Session::_sessionCounter = 0;

bool Session::operator==(int pID){
	return _sessionID == pID;
}

bool Session::operator!=(int pID){
	return _sessionID != pID;
}

bool Session::operator<(int pID){
	return _sessionID < pID;
}

bool Session::operator<=(int pID){
	return _sessionID <= pID;
}

bool Session::operator>(int pID){
	return _sessionID > pID;
}

bool Session::operator>=(int pID){
	return _sessionID >= pID;
}

bool Session::operator==(Session& pSession){
	return _sessionID == pSession.getSessionID();
}

bool Session::operator!=(Session& pSession){
	return _sessionID != pSession.getSessionID();
}

bool Session::operator<(Session& pSession){
	return _sessionID < pSession.getSessionID();
}

bool Session::operator<=(Session& pSession){
	return _sessionID <= pSession.getSessionID();
}

bool Session::operator>(Session& pSession){
	return _sessionID > pSession.getSessionID();
}

bool Session::operator>=(Session& pSession){
	return _sessionID >= pSession.getSessionID();
}


Session::Session(std::string pUser){
	_user = pUser;
	_sessionID = _sessionCounter++;
	_seek = -1;
	_currentPath = "/";
	_disk = 0;
	_currentNode = 0;
	_register = 0;
}
