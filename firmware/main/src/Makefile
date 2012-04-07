BINARY	 = firmware
OBJS	+= main.o 
INCDIR  += -I../../libpacket/src/include 
INCDIR  += -I../../libprocessing/src/include
LIBDIR  += -L../../libpacket/lib 
LIBDIR  += -L../../libprocessing/lib
LIBS	+= -lserial -lconio

include ../../common.mk

check: $(SRC)
	$(CHECKER) $(CHECKERFLAGS) $(SRC)

gen-docs: $(HDR) $(SRC) 
	$(DOXYGEN) $(DOXYGENFLAGS)
