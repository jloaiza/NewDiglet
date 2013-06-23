#ifndef DATABUFFER
#define DATABUFFER

#include "datanode.h"

class DataBuffer{
public:
	void addToBuffer(void* pData, int pType, int pSize);
	DataNode* getBuffer();
	void clear();

private:
	DataNode* _head;
	DataNode* _tail;
};


#endif /* DATABUFFER */