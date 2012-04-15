##
# Toplevel Makefile libpacket 
#
# 07.04.2012, Stefan Wendler, sw@kaltpost.de 
##

BASEDIR 	= .
SRCDIR  	= src
VERSION		= 0.1
TARGET		= libpacket_v$(VERSION)

all: target

world: target gen-docs

prepare:
	test -d lib || mkdir lib
	test -d doc || mkdir doc 

target: prepare 
	make -C $(SRCDIR)

gen-docs: target
	cd $(SRCDIR) && make gen-docs 

style:
	cd $(SRCDIR) && make style

check: 
	make -C $(SRCDIR) check

clean: 
	make -C $(SRCDIR) clean
	rm -fr doc/gen	
	rm -f lib/*.a
