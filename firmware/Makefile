##
# Toplevel Makefile ROCKETuC firmware 
#
# 07.04.2012, Stefan Wendler, sw@kaltpost.de 
##

all: test-target 

clean: clean-lib clean-test 

lib: 
	make -C libpacket
	make -C libprocessing
	make -C main 

test-target: lib
	make -C test/packet 
	make -C test/serial-packet
	make -C test/processing-pin

clean-lib: 
	make -C libpacket clean
	make -C libprocessing clean
	make -C main clean 

clean-test: 
	make -C test/packet clean 
	make -C test/serial-packet clean
	make -C test/processing-pin clean

gen-docs: lib
	make -C libpacket gen-docs 
	make -C libprocessing gen-docs 
	make -C main gen-docs 
