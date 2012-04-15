##
# Toplevel Makefile ROCKETuC firmware 
#
# 07.04.2012, Stefan Wendler, sw@kaltpost.de 
##

all: target test-target 

clean: clean-lib clean-test 

lib: 
	make -C libserial
	make -C libconio
	make -C libpacket
	make -C librocketcore

target: lib
	make -C serial-rocket 

test-target: lib
	make -C test/packet 
	make -C test/packet-serial
	make -C test/rocketcore-pin

clean-lib: 
	make -C libserial clean
	make -C libconio clean
	make -C libpacket clean
	make -C librocketcore clean
	make -C serial-rocket clean 

clean-test: 
	make -C test/packet clean 
	make -C test/packet-serial clean
	make -C test/rocketcore-pin clean

gen-docs: lib
	make -C libserial gen-docs 
	make -C libconio gen-docs 
	make -C libpacket gen-docs 
	make -C librocketcore gen-docs 
	make -C serial-rocket gen-docs 
