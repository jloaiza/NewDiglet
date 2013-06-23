
FIND_PACKAGE(Qt5Core REQUIRED)

SET(LSS_SOURCES
  lss.cpp
  lssconsole.cpp
  lssmain.cpp
  lssmanager.cpp
  lssnetworkhandler.cpp
  lssoperations.cpp
  lssxml.cpp)

ADD_LIBRARY(lss SHARED ${LSS_SOURCES})
QT5_USE_MODULES(lss Xml)
QT5_USE_MODULES(lss XmlPatterns)
