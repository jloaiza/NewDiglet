#ifndef NTREE
#define NTREE

#include <iostream>
#include "ntreenode.h"
#include "ifile.h"
#include "../../include/comparable.h"

class nTree 
{
public:

    nTree();

    void insert(iFile* pFile, nTreeNode* pActual, std::string pName, std::string pPath);

    nTreeNode* getNode(nTreeNode* pActual, std::string pPath);

    void erase(nTreeNode* pActual, std::string pPath);

    void erase(nTreeNode* pNode);

    nTreeNode* getRoot() const {
        return _root;
    }

private:
    nTreeNode* _root;
};

#endif /* NTREE */
