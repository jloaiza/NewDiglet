#include "databuffer.h"

void DataBuffer::addToBuffer(void* pData, int pType, int pSize){
	DataNode* newNode = new DataNode(pData, pType, pSize);
	if (_head == 0){
		_head = _tail = newNode;
	} else {
		_tail->setNext(newNode);
		_tail = newNode;
	}
}

DataNode* DataBuffer::getBuffer(){
	return _head;
}

void DataBuffer::clear(){
	_head = _tail = 0;
}