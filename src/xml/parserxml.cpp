#include "parserxml.h"

void parserxml::createDocument(std::string pDocumentName)
{
	_file.setFileName(QString::fromStdString(pDocumentName));
    updateDocument();
}

void parserxml::loadDocument(std::string pDocumentDirection)
{
    _file.setFileName(QString::fromStdString(pDocumentDirection));
    if(!_file.open( QIODevice::ReadOnly | QIODevice::Text ) )
    {
      qDebug( "Lo sentimos, no se pudo abrir el documento XML." );
    }

    if(!_document.setContent(&_file))
    {
      qDebug("No se pudo parsear el documento XML a un documento de tipo DOM.");
    }
    _file.close();
}

void parserxml::updateDocument()
{
    if( !_file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Lo sentimos, no se pudo crear el documento XML";
    }
    else
    {
        QTextStream  ts( &_file );
        ts << _document.toString();
        _file.close();
        qDebug() << "Archivo XML actualizado con exito.";
    }  
}

bool parserxml::thereFile(std::string pFileDirection)
{
    bool confirmation = false;
    QFile file;
    file.setFileName(QString::fromStdString(pFileDirection));
    if(file.open( QIODevice::ReadOnly | QIODevice::Text ))
    {
        confirmation = true;
    }
    return confirmation;
}

void parserxml::createRoot(std::string pRootName)
{
	QDomElement root = _document.createElement(QString::fromStdString(pRootName));
    _document.appendChild(root);
    updateDocument();
    qDebug() << "Root creada con exito.";
}

void parserxml::createRootChild(std::string pRootChildName)
{
    QDomElement child = _document.createElement(QString::fromStdString(pRootChildName));
    _document.firstChild().appendChild(child);
    updateDocument();
    qDebug() << "Hijo de raíz creado con exito.";

}

void parserxml::createOtherChild(std::string pFatherNodeDirection, std::string pChildName)
{
	QDomElement child = _document.createElement(QString::fromStdString(pChildName));
    QDomElement childadd = tourXML(pFatherNodeDirection);
	childadd.appendChild(child);
    updateDocument();
    qDebug() << "Hijo creado con exito.";

}

void parserxml::createAttribute(std::string pNodeDirection, std::string pAttribute, std::string pAttributeValue)
{
    if(isRoot(pNodeDirection))
    {
        _document.firstChild().toElement().setAttribute(QString::fromStdString(pAttribute),QString::fromStdString(pAttributeValue));
    }
    else
    {
        tourXML(pNodeDirection).setAttribute(QString::fromStdString(pAttribute),QString::fromStdString(pAttributeValue));
    }
    updateDocument();
    qDebug() << "Atributo creado con exito.";
}

void parserxml::createValue(std::string pNodeDirection, std::string pValue)
{
    QDomText value = _document.createTextNode(QString::fromStdString(pValue));
    if(isRoot(pNodeDirection))
    {
        _document.firstChild().appendChild(value);
    }
    else
    {
        tourXML(pNodeDirection).appendChild(value);
    }
    updateDocument();
    qDebug() << "Valor creado con exito.";
}

std::string parserxml::getAnyValue(std::string pNodeDirectionValue)
{
    if( !_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "No se pudo abrir el XML para lectura.";
    }
    else
    {
        QXmlQuery query;
        query.bindVariable("document", &_file);
        std::string stringdocument = "doc($document)";
        std::string finalstring = std::string(stringdocument) + std::string(pNodeDirectionValue);
        query.setQuery(QString::fromStdString(finalstring));
        if(!query.isValid()) 
        {
           qDebug()<< "Xpath invalido.";
        }
        QString queryresult;
        query.evaluateTo(&queryresult);
        if (queryresult == "\n")
        {
            queryresult = "";
        }
        _file.close();
        return queryresult.toStdString();
    }  
}

void parserxml::eraseAttribute(std::string pNodeDirection, std::string pNameAttribute)
{
    if(isRoot(pNodeDirection))
    {
        _document.firstChild().toElement().removeAttribute(QString::fromStdString(pNameAttribute));
    }
    else
    {
        QDomElement childaux = tourXML(pNodeDirection);
        childaux.removeAttribute(QString::fromStdString(pNameAttribute));
    }
    qDebug() << "Atributo borrado con exito.";
    updateDocument();
}

void parserxml::eraseNode(std::string pNodeDirection)
{
    if(isRoot(pNodeDirection))
    {
        _document.removeChild(_document.firstChild());
    }
    else
    {
        int index = getPositionChild(pNodeDirection);
        QDomElement child = tourXML(pNodeDirection);
        QDomElement childfather = child.parentNode().toElement();
        childfather.removeChild(childfather.elementsByTagName(QString::fromStdString(childNameExtract(pNodeDirection))).at(index));
    }
    qDebug() << "Nodo borrado con exito.";
    updateDocument();
}

int parserxml::getPositionChild(std::string pWord)
{
    int finalnumber;
    std::string auxstring = "";
    int index = (pWord.size()-2);
    char letra = pWord.c_str()[index];
    while(!isalpha(letra) && letra != '[')
    {
        auxstring = std::string(1,letra) + std::string(auxstring);
        index--;
        letra = pWord.c_str()[index];
    }
    if(auxstring == "" || auxstring == "1")
    {
        finalnumber = 0;
    }
    else
    {
        finalnumber = atoi(auxstring.c_str()) - 1;
    }
    return finalnumber;
}

int parserxml::caracterPosition(const char *pS, char pC)
{
    const char *p = pS;
    int counter = 1;
    while (*p != pC && *p)
    {
        counter++;
        p++;
    }
    return counter-1;
}

std::string parserxml::wordTokenExtract(std::string pWord)
{
    std::string auxstring;
    char letra = pWord.c_str()[pWord.size()-1];
    if(letra == ']')
    {
        int position = caracterPosition(pWord.c_str(),'[');
        auxstring = pWord.substr(0,position);
    }
    else
    {
        auxstring = pWord;
    }
    return auxstring;
}

QDomElement parserxml::tourXML(std::string pDirection)
{
    QDomElement actualelement = _document.firstChild().toElement();
    std::string completedirection = pDirection;
    std::string delimiter = "/";
    size_t pos = 0;
    std::string token;
    pos = completedirection.find(delimiter);
    completedirection.erase(0, pos + delimiter.length());
    while ((pos = completedirection.find(delimiter)) != std::string::npos) 
    {
        token = completedirection.substr(0, pos);
        int numberchild = getPositionChild(token);
        std::string wordextract = wordTokenExtract(token);
        actualelement = actualelement.elementsByTagName(QString::fromStdString(wordextract)).at(numberchild).toElement();
        completedirection.erase(0, pos + delimiter.length());
    }
    return actualelement;
}

std::string parserxml::childNameExtract(std::string pDirection)
{
    std::string delimiter = "/";
    size_t pos = 0;
    std::string childname;
    std::string wordextract;
    while ((pos = pDirection.find(delimiter)) != std::string::npos) 
    {
        childname = pDirection.substr(0, pos);
        wordextract = wordTokenExtract(childname);
        pDirection.erase(0, pos + delimiter.length());
    }
    return wordextract;
}

bool parserxml::isRoot(std::string pNodeDirection)
{
    bool rootflag = false;
    int counter = 0;
    size_t pos = 0;
    std::string delimiter = "/";
    std::string word;
    while ((pos = pNodeDirection.find(delimiter)) != std::string::npos) 
    {
        pNodeDirection.erase(0, pos + delimiter.length());
        counter++;
    }
    if(!(counter > 1))
    {
        rootflag = true;
    }
    return rootflag;
}