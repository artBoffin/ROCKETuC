##
# Toplevel Makefile libpacket 
#
# 07.04.2012, Stefan Wendler, sw@kaltpost.de 
##

BASEDIR 	= .
SRCDIR  	= src
DEPLOYDIR	= deploy
TMPDIR		= /tmp
VERSION		= 0.1
TARGET		= libpacket_v$(VERSION)

all: target

world: target gen-docs

target: 
	make -C $(SRCDIR)

gen-docs: target
	cd $(SRCDIR) && make gen-docs 

style:
	cd $(SRCDIR) && make style

check: 
	make -C $(SRCDIR) check

deploy-bin: clean target gen-docs 
	rm -fr $(TMPDIR)/$(TARGET)_bin
	mkdir $(TMPDIR)/$(TARGET)_bin
	cp ../../LICENSE README $(TMPDIR)/$(TARGET)_bin/.
	cp -a ./lib $(TMPDIR)/$(TARGET)_bin/.
	cp -a ./doc $(TMPDIR)/$(TARGET)_bin/.
	cp -a ./src/include $(TMPDIR)/$(TARGET)_bin/.
	(cd $(TMPDIR); tar --exclude=".git" -jcvf $(TARGET)_bin.tar.bz2  $(TARGET)_bin)
	mv $(TMPDIR)/$(TARGET)_bin.tar.bz2 $(DEPLOYDIR)/. 
	
deploy: deploy-bin

clean: 
	make -C $(SRCDIR) clean
	rm -fr doc/gen	
	rm -f lib/*.a
