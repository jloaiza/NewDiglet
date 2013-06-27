#ifndef NTREENODE
#define NTREENODE

#include <string>
#include "ifile.h"
#include "../avltree/avltree.h"
#include "../../include/comparable.h"

class nTreeNode 
{	
private:
	std::string getFilesRepAux(TreeNode<nTreeNode>* pNode);

    iFile* _file;
    AVLTree<nTreeNode, std::string>* _children;
    nTreeNode* _parent;
    std::string _name;
    std::string _path;
    std::string _user;
    

public:
	nTreeNode(iFile* pFile, std::string pName, std::string pUser);
	std::string getFilesRep();

	bool operator==(std::string& pNode){
		return _name == pNode;
	}

	bool operator<=(std::string& pNode){
		return _name <= pNode;
	}

	bool operator<(std::string& pNode){
		return _name < pNode;
	}

	bool operator>=(std::string& pNode){
		return _name >= pNode;
	}
	bool operator>(std::string& pNode){
		return _name > pNode;
	}

	bool operator==(nTreeNode& pNode){
		return _name == pNode.getName();
	}

	bool operator<=(nTreeNode& pNode){
		return _name <= pNode.getName();
	}

	bool operator<(nTreeNode& pNode){
		return _name < pNode.getName();
	}

	bool operator>=(nTreeNode& pNode){
		return _name >= pNode.getName();
	}

	bool operator>(nTreeNode& pNode){
		return _name > pNode.getName();
	}

	iFile* getFile() const {
		return _file;
	}

	std::string getName() const {
		return _name;
	}

	std::string getPath() const {
		return _path;
	}

	void setPath(std::string pPath){
		_path = pPath;
	}

	std::string getUser() const {
		return _user;
	}

	void setUser(std::string pUser){
		_user = pUser;
	}

	std::string getTotalPath() const {
		return _path + _name;
	}

	nTreeNode* getParent() const {
		return _parent;
	}

	void setParent(nTreeNode* pParent){
		_parent = pParent;
	}

	nTreeNode* getChild(std::string pName) const {
		return _children->search(&pName);
	}

	void eraseChild(std::string pName){
		_children->erase(&pName);
	}

	void addChild(nTreeNode* pChild){
		_children->insert(pChild);
		pChild->setParent(this);
	}

	AVLTree<nTreeNode, std::string>* getChildren() const {
		return _children;
	}
};

#endif /* NTREENODE */
