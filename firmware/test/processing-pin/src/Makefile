BINARY	 = firmware
OBJS	+= main.o 
INCDIR  += -I../../../libprocessing/src/include 
LIBDIR  += -L../../../libprocessing/lib
LIBS	+= -lserial -lconio -lprocessing

include ../../../common.mk

check: $(SRC)
	$(CHECKER) $(CHECKERFLAGS) $(SRC)

gen-docs: $(HDR) $(SRC) 
	$(DOXYGEN) $(DOXYGENFLAGS)
