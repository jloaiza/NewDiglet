#include <QtXml>
#include <QtCore>
#include <QtDebug>
#include <QXmlQuery>
#include <iostream>
#include <string>
#include <sstream>

class parserxml
{
public:
	/**
	* Método para crear un documento XML.
	* @param pDocumentName: El nombre del documento que será creado, se puede dar un nombre únicamente ("ejemplo.xml")
	* o bien la dirección donde quiere que se cree el documento ("home/usuario/Desktop/ejemplo.xml")
	*/
	void createDocument(std::string pDocumentName);
	/**
	* Método para cargar un documento XML que ya ha sido creado con anterioridad.
	* @param pDocumentDirection: Corresponde a la dirección exacta de dónde se ubica el documento XML a cargar,
	* de igual forma se puede pasar únicamente el nombre del documento que se encuentre en la misma ruda
	* de este archivo.
	*/
	void loadDocument(std::string pDocumentDirection);
	/**
	* Método para actualizar cualquier cambio que se le haga al XML en el documento.
	*/
	void updateDocument();
	/**
	* Método que crea una raíz dentro del documento XML.
	* @param pRootName: Nombre de la raíz que será creada dentro del XML.
	*/
	void createRoot(std::string pRootName);
	/**
	* Método para crear algún hijo a la raiz del documento XML.
	* @param pRootChildName: Nombre que se le dará al nuevo hijo de la raíz.
	*/
	void createRootChild(std::string pRootChildName);
	/**
	* Método para crear hijos a cualquier nodo distinto de la raíz.
	* @param pFatherNodeDirection: Dirección EXACTA del nodo al que se le creará el nuevo hijo.
	* @param pChildName: Nombre que se le dará al nuevo hijo.
	* Nota: Es MUY importante que cualquier dirección que sea dada para "pFatherNodeDirection" no empiece con "/" pero si termine con ella.
	*/
	void createOtherChild(std::string pFatherNodeDirection, std::string pChildName);
	/**
	* Método para crear un atributo a cualquier nodo del documento XML.
	* @param pNodeDirection: Dirección EXACTA del nodo al que se le creará el atributo.
	* @param pAttribute: Nombre que se la dará al atributo.
	* @param pAttributeValue: Valor que se dará al atributo.
	* Nota: Es MUY importante que cualquier dirección que sea dada para "pNodeDirection" no empiece con "/" pero si termine con ella.
	* Nota 2: Si al intentar crear un atributo para algún nodo se tiene el problema que existen dos nodos cuyo nombre son el mismo 
	* se puede utilizar los [indice] donde "indice" corresponde al número del nodo cuyos nombres son iguales.
	* Ejemplo: Se tiene un documento cuya raíz es "ROOT" la cual tiene dos hijos llamados "EXAMPLE" y se quiere agregar
	* un atributo nuevo al nodo "EXAMPLE" numero dos, de esta forma la dirección para "pNodeDirection" será: "ROOT/EXAMPLE[2]/"
	* Como se puede observar el número "2" corresponde al nodo al que se quiere agregar el atributo, esto sólo es valido cuando
	* existen nodos con nombres iguales, siempre que no se especifique ningún indice usando [indice] se asume que se quiere
	* agregar el nuevo atributo al primer nodo.
	*/
	void createAttribute(std::string pNodeDirection, std::string pAttribute, std::string pAttributeValue);
	/**
	* Método para asignar un valor a cualquier nodo del documento XML.
	* @param pNodeDirection: Dirección EXACTA del nodo al que se le asignará el nuevo valor.
	* @param pValue: Corresponde al valor que se asignaŕa al nodo.
	* Nota: Es MUY importante que cualquier dirección que sea dada para "pNodeDirection" no empiece con "/" pero si termine con ella.
	* Nota 2: Si al intentar asignar un valor para algún nodo se tiene el problema que existen dos nodos cuyo nombre son el mismo 
	* se puede utilizar los [indice] donde "indice" corresponde al número del nodo cuyos nombres son iguales.
	* Ejemplo: Se tiene un documento cuya raíz es "ROOT" la cual tiene dos hijos llamados "EXAMPLE" y se quiere asignar
	* un valor nuevo al nodo "EXAMPLE" numero dos, de esta forma la dirección para "pNodeDirection" será: "ROOT/EXAMPLE[2]/"
	* Como se puede observar el número "2" corresponde al nodo al que se quiere asignar el valor, esto sólo es valido cuando
	* existen nodos con nombres iguales, siempre que no se especifique ningún indice usando [indice] se asume que se quiere
	* asignar el nuevo valor al primer nodo.
	*/
	void createValue(std::string pNodeDirection, std::string pValue);
	/**
	* Método para borrar cualquier nodo del documento XML.
	* @param pNodeDirection: Dirección EXACTA del nodo que se quiere borrar.
	* Nota: Es MUY importante que cualquier dirección que sea dada para "pNodeDirection" no empiece con "/" pero si termine con ella.
	* Nota 2: Si al intentar borrar un nodo se tiene el problema que existen dos nodos cuyo nombre son el mismo 
	* se puede utilizar los [indice] donde "indice" corresponde al número del nodo cuyos nombres son iguales.
	* Ejemplo: Se tiene un documento cuya raíz es "ROOT" la cual tiene dos hijos llamados "EXAMPLE" y se quiere borrar
	* el nodo "EXAMPLE" numero dos, de esta forma la dirección para "pNodeDirection" será: "ROOT/EXAMPLE[2]/"
	* Como se puede observar el número "2" corresponde al nodo que se quiere borrar, esto sólo es valido cuando
	* existen nodos con nombres iguales, siempre que no se especifique ningún indice usando [indice] se asume que se quiere
	* borrar el primer nodo.
	*/
	void eraseNode(std::string pNodeDirection);
	/**
	* Método para borrar cualquier atributo correspondiente a algún nodo del XML.
	* @param pNodeDirection: Dirección EXACTA del nodo al que se quiere borrar el atributo.
	* @param pNameAttribute: Nombre del atributo que será borrado del nodo.
	* Nota: Es MUY importante que cualquier dirección que sea dada para "pNodeDirection" no empiece con "/" pero si termine con ella.
	* Nota 2: Si al intentar borrar un atributo de algún nodo se tiene el problema que existen dos nodos cuyo nombre son el mismo 
	* se puede utilizar los [indice] donde "indice" corresponde al número del nodo cuyos nombres son iguales.
	* Ejemplo: Se tiene un documento cuya raíz es "ROOT" la cual tiene dos hijos llamados "EXAMPLE" y se quiere borrar
	* un atributo del nodo "EXAMPLE" numero dos, de esta forma la dirección para "pNodeDirection" será: "ROOT/EXAMPLE[2]/"
	* Como se puede observar el número "2" corresponde al nodo que se quiere borrar el atributo, esto sólo es valido cuando
	* existen nodos con nombres iguales, siempre que no se especifique ningún indice usando [indice] se asume que se quiere
	* borrar el atributo del primer nodo.
	*/
	void eraseAttribute(std::string pNodeDirection, std::string pNameAttribute);
	/**
	* Método para obtener el valor asignado a cualquier nodo, asi como sus atributos (Utiliza XPATH para la consulta).
	* @param pNodeDirectionValue: Dirección exacta del nodo al que se quiere extraer el valor.
	* Nota: Es MUY importante que cualquier dirección que sea dada para "pNodeDirectionValue" empiece con "/" pero NO termine con ella.
	* Nota 2: Para más información de como realizar consultas con XPATH puede visitar el siguiente enlace
	* Enlace: www.google.co.cr
	*/
	std::string getAnyValue(std::string pNodeDirectionValue);
	/**
	* Función que evalua si la direción de un archivo dado existe.
	*/
	bool thereFile(std::string pFileDirection);
private:
	/** Los siguientes métodos son únicos para el manejo del XML interno y no debe de ser modificados bajo ninguna circunstancia. */
	/** ------------------------------------------------------------------------------------------------------------------------ */

	/**
	* Método que se encarga de recorrer una dirección y me devuelve el nodo asociado a la misma.
	*/
	QDomElement tourXML(std::string pDirection);
	/**
	* Método que elimina el indice ([indice]) de una palabra y la devuelve nitida.
	*/
	std::string wordTokenExtract(std::string pWord);
	/**
	* Método devuelve el nombre del último nodo en una dirección.
	*/
	std::string childNameExtract(std::string pDirection);
	/**
	* Método que se encarga de dar el indice en una palabra ([indice]).
	*/
	int getPositionChild(std::string pWord);
	/**
	* Método que devuelve la posición de un caracter dentro de una cadena de caracteres.
	*/
	int caracterPosition(const char *pS , char pC);
	/**
	* Método para saber si una dirección dada corresponde a la dirección de nodo raíz del documento XML.
	*/
	bool isRoot(std::string pNodeDirection);

    /** Varaible de uso general */
    /** ----------------------- */

    /**
    * Documentl XML que se usa para trabajar sobre el.
    */
	QDomDocument _document;
	/**
	* Archivo en DISCO donde se escribe el documento XML.
	*/
	QFile _file;
};