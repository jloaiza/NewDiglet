 
#ifndef REGISTERBUFFER
#define REGISTERBUFFER

#include <string>
#include "registerspace.h"

class RegisterBuffer
{
private:
	RegisterSpace* _head;
	RegisterSpace* _tail;
public:
	RegisterBuffer(){
		_head = _tail = 0;
	}

	void addSpace(std::string pName, int pSize, short pType);
	RegisterSpace* getBuffer();
	void clear();
};

#endif
