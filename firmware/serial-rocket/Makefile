##
# Toplevel Makefile ROCKETuC firmware
#
# 07.04.2012, Stefan Wendler, sw@kaltpost.de
##

BASEDIR 	= .
SRCDIR  	= src
BINDIR		= bin
FIRMWARE    = firmware.elf
DEPLOYDIR	= deploy
TMPDIR		= /tmp
VERSION		= 0.1
TARGET		= ROCKETuC-firmware-msp430g2553-launchpad_v$(VERSION)

all: target

world: target gen-docs

prepare:
	test -d bin || mkdir bin 
	test -d doc || mkdir doc 

target: prepare
	make -C $(SRCDIR)

gen-docs: target
	cd $(SRCDIR) && make gen-docs

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
