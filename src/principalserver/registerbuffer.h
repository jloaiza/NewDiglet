 
#ifndef REGISTERBUFFER
#define REGISTERBUFFER

#include <string>
#include "registerspace.h"

class RegisterBuffer
{
private:
	RegisterSpace* _head;
	RegisterSpace* _tail;
	int _length;
public:
	RegisterBuffer(){
		_head = _tail = 0;
		_length = 0;
	}

	void addSpace(std::string pName, int pSize, short pType);

	RegisterSpace* getBuffer() const{
		return _head;
	}

	void clear();
	int getRegisterSize();

	int getLength() const{
		return _length;
	}
};

#endif
