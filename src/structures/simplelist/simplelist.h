
#ifndef SIMPLELIST_H
#define SIMPLELIST_H

#include <string>

class Node;
class Comparable;

class SimpleList{

public:

	int _size;
    Node* _head;

    /**
     * @brief SimpleList
     */
    SimpleList();
	
    /**
     * @brief insert
     * @param pData
     */
    void insert(Comparable* pData);

    /**
     * @brief search
     * @param pData
     * @return
     */
    bool search(std::string pName);

    /**
     * @brief erase
     * @param pData
     */
    void erase(Comparable *pData);

    /**
     * @brief get
     * @param pName
     * @return
     */
    Comparable* get(std::string pName);

    /**
     * @brief print
     */
	void print();
	
};

#endif
