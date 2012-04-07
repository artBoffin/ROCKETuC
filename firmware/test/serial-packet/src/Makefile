BINARY	 = firmware
OBJS	+= main.o 
INCDIR  += -I../../../libpacket/src/include 
LIBDIR  += -L../../../libpacket/lib
LIBS	+= -lserial -lconio -lpacket

include ../../../common.mk

check: $(SRC)
	$(CHECKER) $(CHECKERFLAGS) $(SRC)

gen-docs: $(HDR) $(SRC) 
	$(DOXYGEN) $(DOXYGENFLAGS)
