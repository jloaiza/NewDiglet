#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

static const short BOOL   = 1;
static const short CHAR   = 2;
static const short SHORT  = 3;
static const short INT    = 4;
static const short DOUBLE = 5;
static const short STRING = 6;

std::string lssmenuL = "** * * * * * * * * * * * * * * * * *";
std::string lssmenuS = "*                                  *";
std::string lssmenu3 = "*     seleccione la operacion:     *";
std::string lssmenu4 = "*       1. Crear disco nuevo       *";
std::string lssmenu5 = "*       2. Borrar disco            *";
std::string lssmenu6 = "*       3. Mostrar discos          *";
std::string lssmenu7 = "*       4. SAVE                    *";
std::string lssmenu8 = "*       5. LOAD                    *";
std::string lssmenu9 = "*       6. Salir                   *";

std::string NAME = "nombre del disco (archivo real): ";
std::string NAME2 = "nombre del xml: ";
std::string SIZE1 = "tamaño del disco (bytes): ";
std::string PASS = "security key: ";

// Constants for MD5Transform routine.

const int S11 = 7;
const int S12 = 12;
const int S13 = 17;
const int S14 = 22;
const int S21 = 5;
const int S22 = 9;
const int S23 = 14;
const int S24 = 20;
const int S31 = 4;
const int S32 = 11;
const int S33 = 16;
const int S34 = 23;
const int S41 = 6;
const int S42 = 10;
const int S43 = 15;
const int S44 = 21;

namespace PS
{
  

int INT_TYPE    = 0;
int LONG_TYPE   = 1;
int STRING_TYPE = 2;
int DOUBLE_TYPE = 3;
int SHORT_TYPE  = 4;
int SEEK_POS    = -1;
int NO_SESSION  = -1;

}


#endif // CONSTANTS_H
