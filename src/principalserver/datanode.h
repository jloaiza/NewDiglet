#ifndef DATANODE
#define DATANODE

class DataNode{
public:
	DataNode(void* pData, int pType, int pSize){
		_data = pData;
		_type = pType;
		_size = pSize;
		_next = 0;
	}
	
	void* getData() const{
		return _data;
	}

	int getType() const {
		return _type;
	}

	int getSize() const {
		return _size;
	}

	DataNode* getNext() const {
		return _next;
	}

	void setNext(DataNode* pNode){
		_next = pNode;
	}

	void releaseDependencyList();
	
private:
	void* _data;
	int _size;
	int _type;
	DataNode* _next;

};

#endif /* DATANODE */