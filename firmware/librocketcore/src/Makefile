LIBNAME  = librocketcore
INCDIR  += -I../../libpacket/src/include 
INCDIR  += -I../../libconio/src/include 
OBJS    += pin_msp430.o core_proto.o core_handlers.o core_handlers_msp430.o packet_handler.o

include ../../common_lib.mk

check: $(SRC)
	$(CHECKER) $(CHECKERFLAGS) $(SRC)

gen-docs: $(HDR) $(SRC)
	$(DOXYGEN) $(DOXYGENFLAGS)
