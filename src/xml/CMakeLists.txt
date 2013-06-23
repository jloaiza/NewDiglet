

FIND_PACKAGE(Qt5Core REQUIRED)
# FIND_PACKAGE(Qt5Xml REQUIRED)

SET(XML_SOURCES
  clientsxml.cpp
  diskgroupsxml.cpp
  parserxml.cpp
  usersxml.cpp)

ADD_LIBRARY(xml SHARED ${XML_SOURCES})
QT5_USE_MODULES(xml Xml)
QT5_USE_MODULES(xml XmlPatterns)