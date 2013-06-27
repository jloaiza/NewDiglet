#include "ntree.h"
#include <iostream>
#include "../../tokenizer/tokenizer.h"

nTree::nTree()
{
    _root = new nTreeNode(NULL, "", "");
}

void nTree::insert(iFile* pFile, nTreeNode* pActual, std::string pName, std::string pUser, std::string pPath){
    nTreeNode* toInsert = getNode(pActual, pPath);
    if (toInsert == 0){
        return;
    }
    nTreeNode* newNode = new nTreeNode(pFile, pName, pUser);
    newNode->setPath( toInsert->getTotalPath() + "/" );
    toInsert->addChild(newNode);
}

nTreeNode* nTree::getNode(nTreeNode* pActual, std::string pPath){
    nTreeNode* iNode;
    if (pActual == 0){
        iNode = _root;
    } else {
        iNode = pActual;
    }

    std::string toMove = Tokenizer::getCommandSpace(pPath, 1, '/');
    for (int i = 1; iNode != 0 && toMove != ""; i++){
        std::cout<<"to move: "<<toMove<<std::endl;
        if (toMove == ".."){
            iNode = iNode->getParent();
        } else {
            iNode = iNode->getChild(toMove);
        }
        toMove = Tokenizer::getCommandSpace(pPath, i+1, '/');
    }
    
    return iNode;
}

void nTree::erase(nTreeNode* pActual, std::string pPath){
    nTreeNode* toErase = getNode(pActual, pPath);
    if (toErase != 0 && toErase != _root){
        toErase->getParent()->eraseChild(toErase->getName());
    }
}

void nTree::erase(nTreeNode* pNode){
    if (pNode != _root){
        pNode->getParent()->eraseChild(pNode->getName());
    }
}