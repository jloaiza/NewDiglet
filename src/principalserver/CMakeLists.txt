
SET(PRINCIPAL_SERVER_SOURCES
  databuffer.cpp
  datanode.cpp
  disk.cpp
  # generalmanager.cpp
  # noraid.cpp
  registerbuffer.cpp
  registerspace.cpp
  serverconsole.cpp
  servernetworkhandler.cpp
  serveroperations.cpp
  session.cpp
  storageclient.cpp
  user.cpp)


ADD_LIBRARY(principalserver SHARED ${PRINCIPAL_SERVER_SOURCES})