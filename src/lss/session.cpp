#include "session.h"

int Session::_count = 0;

Session::Session(){
	_id = _count++;
	_lss = new DoubleLinkedList<Lss, short>();
}

Lss* Session::getLss(short pID) const{
	return _lss->search(&pID);
}

void Session::addLss(Lss* pLss){
	_lss->insertEnd(pLss);
}

bool Session::operator==(int& pSession){
	return _id == pSession;
}

bool Session::operator!=(int& pSession){
	return _id != pSession;
}

bool Session::operator<=(int& pSession){
	return _id <= pSession;
}

bool Session::operator<(int& pSession){
	return _id < pSession;
}

bool Session::operator>=(int& pSession){
	return _id >= pSession;
}

bool Session::operator>(int& pSession){
	return _id > pSession;
}


bool Session::operator==(Session& pSession){
	return _id == pSession.getID();
}

bool Session::operator!=(Session& pSession){
	return _id != pSession.getID();
}

bool Session::operator<=(Session& pSession){
	return _id <= pSession.getID();
}

bool Session::operator<(Session& pSession){
	return _id < pSession.getID();
}

bool Session::operator>=(Session& pSession){
	return _id >= pSession.getID();
}

bool Session::operator>(Session& pSession){
	return _id > pSession.getID();
}