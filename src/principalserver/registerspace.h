
#ifndef REGISTERSPACE
#define REGISTERSPACE
 
#include <string>

class RegisterSpace
{
private:
	std::string _name;
	int _size;
	int _type;
	RegisterSpace * _next;
public:
	RegisterSpace(std::string pName, int pSize, int pType);
	std::string getName();
	int getSize();
	int totalLength();
	int getType();
	RegisterSpace * getNext();
	void setNext (RegisterSpace * pRegisterSpace);
	void releaseDependencyList();
};

#endif
