BINARY	 = firmware
OBJS	+= main.o serial_transport_msp430.o 
INCDIR  += -I../../libserial/src/include 
INCDIR  += -I../../libpacket/src/include 
INCDIR  += -I../../librocketcore/src/include
LIBDIR  += -L../../libserial/lib 
LIBDIR  += -L../../libpacket/lib 
LIBDIR  += -L../../librocketcore/lib
LIBS	+= -lserial -lrocketcore -lpacket

include ../../common.mk

check: $(SRC)
	$(CHECKER) $(CHECKERFLAGS) $(SRC)

gen-docs: $(HDR) $(SRC) 
	$(DOXYGEN) $(DOXYGENFLAGS)
