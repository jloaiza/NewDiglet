#ifndef CONSTANTS
#define CONSTANTS

#include <string>

static const short BOOL   = 1;
static const short CHAR   = 2;
static const short SHORT  = 3;
static const short INT    = 4;
static const short DOUBLE = 5;
static const short STRING = 6;

static const std::string lssmenuL = "** * * * * * * * * * * * * * * * * *";
static const std::string lssmenuS = "*                                  *";
static const std::string lssmenu3 = "*     seleccione la operacion:     *";
static const std::string lssmenu4 = "*       1. Crear disco nuevo       *";
static const std::string lssmenu5 = "*       2. Borrar disco            *";
static const std::string lssmenu6 = "*       3. Mostrar discos          *";
static const std::string lssmenu7 = "*       4. SAVE                    *";
static const std::string lssmenu8 = "*       5. LOAD                    *";
static const std::string lssmenu9 = "*       6. Salir                   *";

static const std::string NAME = "nombre del disco (archivo real): ";
static const std::string NAME2 = "nombre del xml: ";
static const std::string SIZE1 = "tamaño del disco (bytes): ";
static const std::string PASS = "security key: ";

// Constants for MD5Transform routine.

static const int S11 = 7;
static const int S12 = 12;
static const int S13 = 17;
static const int S14 = 22;
static const int S21 = 5;
static const int S22 = 9;
static const int S23 = 14;
static const int S24 = 20;
static const int S31 = 4;
static const int S32 = 11;
static const int S33 = 16;
static const int S34 = 23;
static const int S41 = 6;
static const int S42 = 10;
static const int S43 = 15;
static const int S44 = 21;

namespace PS
{  

	static const int INT_TYPE    = 0;
	static const int LONG_TYPE   = 1;
	static const int STRING_TYPE = 2;
	static const int DOUBLE_TYPE = 3;
	static const int SHORT_TYPE  = 4;
	static const int SEEK_POS    = -1;
	static const int NO_SESSION  = -1;

}


#endif // CONSTANTS
