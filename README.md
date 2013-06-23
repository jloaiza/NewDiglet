DIGLET
======


Para compilar por primera vez (lento):
-------------------------------------

Ubicarse en el directorio principal:

* qmake
* make


Paquetes necesarios a tener instalados (Ubuntu 13.04):
-----------------------------------------------------

* libqt5core5
* libqt5xml5
* libqt5xmlpatterns5-dev
* Alguna otra que ahora no me acuerdo

Para compilaciones sucesivas (rápido):
--------------------------------------

* make

Para compilaciones sucesivas desde cero (lento):
-----------------------------------------------

* qmake
* make clean
* make

Para agregar archivos nuevos a la lista de archivos para compilar:
-----------------------------------------------------------------

* Buscar en la carpeta del archivo nuevo el archivo con extensión .pro o .pri. Ahí agregar el archivo a la lista
de SOURCES o HEADERS según sea necesario. No tocar nada más.

