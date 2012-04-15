LIBNAME	 = libserial
OBJS	+= serial_rb.o 
OBJS	+= serial_usci_msp430.o

include ../../common_lib.mk

check: $(SRC)
	$(CHECKER) $(CHECKERFLAGS) $(SRC)

gen-docs: $(HDR) $(SRC)
	$(DOXYGEN) $(DOXYGENFLAGS)
