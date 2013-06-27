#include "registerspace.h"

RegisterSpace::RegisterSpace(std::string pName, int pSize, int pType)
{
	_name = pName;
	_size = pSize;
	_type = pType;
    _next = 0;
}

std::string RegisterSpace::getName()
{
	return _name;
}

int RegisterSpace::getSize()
{
	return _size;
}

int RegisterSpace::totalLength(){
	int length = 0;
	RegisterSpace* iSpace = this;
	while(iSpace != 0){
		length++;
		iSpace = iSpace->getNext();
	}
	return length;
}

int RegisterSpace::getType()
{
	return _type;
}

RegisterSpace * RegisterSpace::getNext()
{
	return _next;
}

void RegisterSpace::setNext (RegisterSpace * pNext)
{
	_next = pNext;
}

void RegisterSpace::releaseDependencyList(){
	RegisterSpace* iSpace = this;
	while (iSpace != 0){
		RegisterSpace* tmp = iSpace->getNext();
		delete iSpace;
		iSpace = tmp;
	}
}