#ifndef SESSION
#define SESSION

#include "../structures/doublelinkedlist/doublelinkedlist.h"
#include "lss.h"

class Session{
private:
	DoubleLinkedList<Lss, short>* _lss;
	int _id;
	static int _count;

public:
	Session();

	int getID() const {
		return _id;
	}

	Lss* getLss(short pID) const;

	void addLss(Lss* pLss);

	bool operator==(int& pSession);
	bool operator!=(int& pSession);
	bool operator<=(int& pSession);
	bool operator<(int& pSession);
	bool operator>=(int& pSession);
	bool operator>(int& pSession);

	bool operator==(Session& pSession);
	bool operator!=(Session& pSession);
	bool operator<=(Session& pSession);
	bool operator<(Session& pSession);
	bool operator>=(Session& pSession);
	bool operator>(Session& pSession);
};




#endif
