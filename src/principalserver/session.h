#ifndef SESSION
#define SESSION

#include <string>
#include "registerspace.h"
#include "diskgroup.h"
#include "../structures/ntree/ntreenode.h"

class Session {
private:

	static int _sessionCounter;
	int _sessionID;
	int _seek;
	DiskGroup* _disk;
	nTreeNode* _currentNode;
	RegisterSpace* _register;
	std::string _user;

public:
	Session(std::string pUser, DiskGroup* pDisk);
	
	bool operator==(int pID);
	bool operator!=(int pID);
	bool operator<(int pID);
	bool operator<=(int pID);
	bool operator>(int pID);
	bool operator>=(int pID);

	bool operator==(Session& pSession);
	bool operator!=(Session& pSession);
	bool operator<(Session& pSession);
	bool operator<=(Session& pSession);
	bool operator>(Session& pSession);
	bool operator>=(Session& pSession);

	int getSessionID() const{
		return _sessionID;
	}

	int getSeek() const {
		return _seek;
	}

	void setSeek(int pSeek){
		_seek = pSeek;
	}

	DiskGroup* getDiskGroup() const {
		return _disk;
	}

	nTreeNode* getCurrentNode() const {
		return _currentNode;
	}

	void setCurrentNode(nTreeNode* pNode){
		_currentNode = pNode;
	}

	RegisterSpace* getCurrentFormat() const {
		return _register;
	}

	void setCurrentFormat(RegisterSpace* pFormat){
		_register = pFormat;
	}

	std::string getUser() const{
		return _user;
	}
};


#endif /* SESSION */