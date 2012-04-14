##
# Toplevel Makefile
#
# Stefan Wendler, sw@kaltpost.de
##

BASEDIR 	= .
SRCDIR  	= src
BINDIR		= bin
FIRMWARE    = firmware.elf
DEPLOYDIR	= deploy
TMPDIR		= /tmp
VERSION		= 0.1
TARGET		= librocketcore-pin-test_v$(VERSION)

all: target

prepare:
	test -d bin || mkdir bin 

target: prepare
	make -C $(SRCDIR)

style:
	cd $(SRCDIR) && make style

check:
	make -C $(SRCDIR) check

flash-target: target
	mspdebug rf2500 "prog $(BINDIR)/$(FIRMWARE)"

clean:
	make -C $(SRCDIR) clean
	rm -fr doc/gen
	rm -f bin/firmware.*
