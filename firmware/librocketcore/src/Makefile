LIBNAME  = librocketcore
INCDIR  += -I../../libpacket/src/include 
OBJS    += pin_msp430.o core_proto.o core_handlers.o packet_handler.o

include ../../common_lib.mk

check: $(SRC)
	$(CHECKER) $(CHECKERFLAGS) $(SRC)

gen-docs: $(HDR) $(SRC)
	$(DOXYGEN) $(DOXYGENFLAGS)
