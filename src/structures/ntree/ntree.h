
#ifndef NTREE_H
#define NTREE_H

#include <string>

class nTreeNode;
class iFile;


class nTree {

private:

    nTreeNode* _head;

public:

    /**
     * @brief nTree
     */
    nTree();

    /**
     * @brief create
     * @param pName
     * @param pFile
     * @param pPath
     */
    void insert(std::string pName, iFile* pFile, std::string pPath);

    /**
     * @brief erase
     * @param pPath
     */
    void erase(std::string pPath);

    /**
     * @brief getNode
     * @param pPath
     * @return
     */
    nTreeNode* getNode(std::string pPath);

    /**
     * @brief getHead
     * @return
     */
    nTreeNode* getHead();
};

#endif
