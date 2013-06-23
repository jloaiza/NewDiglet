
BUILDDIR := build
SRCDIR := src

all: builddir release

debug: builddir
	cd $(BUILDDIR); \
	cmake -DCMAKE_BUILD_TYPE=Debug ../$(SRCDIR); \
	make --no-print-directory 

release: builddir
	cd $(BUILDDIR); \
	cmake ../$(SRCDIR); \
	make --no-print-directory 
	
builddir:
	test -d $(BUILDDIR) || mkdir $(BUILDDIR)

run-lss: builddir release
	./$(BUILDDIR)/bin/lssprovider

run-server: builddir release
	./$(BUILDDIR)/bin/serverprovider

run-client: builddir release
	./$(BUILDDIR)/bin/clientprovider

run: builddir release
	./$(BUILDDIR)/bin/test

clean:
	rm -rf $(BUILDDIR)/*
	
