
#ifndef NTREENODE
#define NTREENODE

#include <string>

class SimpleList;
class Comparable;
class iFile;

class nTreeNode {
	
private:
	
    Comparable* _file;
    SimpleList* _children;
	
public:

    std::string name;

    /**
     * @param pFile archivo que almacenará
     * @param pUser usuario dueño del archivo o carpeta
     */
    nTreeNode (Comparable* pPath, std::string pUser);
	
    /**
     * agrega un hijo a la lista simple del nodo
     * @param pNode nuevo nodo
     */
    void addChild(nTreeNode pNode);

    /**
     * retorna el hijo de un nodo
     * @return
     */
    iFile* getChild(std::string pName);

    //SimpleList* getChildrenList();

    /**
     * busca si existe un hijo del nodo
     * @param pName nombre del hijo que se busca
     * @return true si el hijo existe, false de lo contrario
     */
    bool searchChild(std::string pName);

    /**
     * @brief eraseChild
     * @param pName
     */
    void eraseChild(std::string pName);

    /**
     * @brief print
     */
	void print();
	
};
#endif


