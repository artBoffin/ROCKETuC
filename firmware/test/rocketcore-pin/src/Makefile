BINARY	 = firmware
OBJS	+= main.o 
INCDIR  += -I../../../libserial/src/include 
INCDIR  += -I../../../libconio/src/include 
INCDIR  += -I../../../librocketcore/src/include 
LIBDIR  += -L../../../libserial/lib
LIBDIR  += -L../../../libconio/lib
LIBDIR  += -L../../../librocketcore/lib
LIBS	+= -lserial -lconio -lrocketcore

include ../../../common.mk

check: $(SRC)
	$(CHECKER) $(CHECKERFLAGS) $(SRC)

gen-docs: $(HDR) $(SRC) 
	$(DOXYGEN) $(DOXYGENFLAGS)
