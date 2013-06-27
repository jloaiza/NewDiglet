#include "ntree.h"
#include "ntreenode.h"

int main()
{
	nTree* prueba = new nTree();
	nTreeNode* aux = prueba->getNode(0, "");
	std::cout << aux->getTotalPath() << std::endl;
	prueba->insert(0, aux, "JAJA", "jloaiza" ,  "");
	prueba->insert(0, aux, "1", "jloaiza" ,  "");
	prueba->insert(0, aux, "50", "jloaiza" ,  "");
	prueba->insert(0, aux, "20", "jloaiza" ,  "");
	prueba->insert(0, aux, "JAJA2", "jloaiza" ,  "JAJA");
	std::cout<<"to get:"<<std::endl;
	nTreeNode* getted = prueba->getNode(0, "JAJA");
	std::cout << getted->getTotalPath() << std::endl;
	std::cout << getted->getName() << std::endl;
	prueba->erase(aux, "JAJA/JAJA2");
	std::cout<<prueba->getNode(0, "JAJAsd")<<std::endl;
	std::cout<<aux->getFilesRep()<<std::endl;
	return 0;
}

// g++ -std=c++11 ntree.cpp ntreenode.cpp main.cpp ../../tokenizer/tokenizer.cpp -o main
