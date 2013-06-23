

SET(STRUCTURES_SOURCES
  ntree/ntree.cpp
  ntree/ntreenode.cpp
  simplelist/simplelist.cpp
  simplelist/node.cpp)


ADD_LIBRARY(structures SHARED ${STRUCTURES_SOURCES})