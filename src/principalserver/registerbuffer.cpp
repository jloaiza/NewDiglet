#include "registerbuffer.h"

void RegisterBuffer::addSpace(std::string pName, int pSize, short pType){
	RegisterSpace* newSpace = new RegisterSpace(pName, pSize, pType);
	if (_head == 0){
		_head = _tail = newSpace;
	} else {
		_tail->setNext(newSpace);
		_tail = newSpace;
	}
}

RegisterSpace* RegisterBuffer::getBuffer(){
	return _head;
}

/**
* This method does not release the memory of the RegisterSpace's that he contains, it just set the head and tail to NULL
* in order to make a new list of RegisterSpace's. To release the memory of the RegisterSpace's you have to call the
* method releaseDepedencyList of the head
*/
void RegisterBuffer::clear(){
	_head = _tail = 0;
}