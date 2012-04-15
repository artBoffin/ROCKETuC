##
# Common settings for all project Makefiles that produce libraries
#
# 07.04.2012, Stefan Wendler, sw@kaltpost.de
##

PREFIX      ?= msp430-

CC			 = $(PREFIX)gcc
AR			 = $(PREFIX)ar

CFLAGS		+= -Os -g -mmcu=msp430g2553 -Wall -Wextra $(INCDIR) 
ARFLAGS		 = rcs

# where to search for headers
INCDIR      += -I./include -I$(HOME)/msp430/include

# where to put generated libraries to
LIBDIR		 = ../lib

# doxygen executable
DOXYGEN = doxygen

# doxygen flags
DOXYGENFLAGS = ../doxygen.conf

# styler to use
STYLER = astyle

# which c-style to use
# - see man astyle
STYLERFLAGS = --style=stroustrup

# cpp checker
CHECKER = cppcheck

# flags for checker
# CHECKERFLAGS = --error-exitcode=1 --enable=all
CHECKERFLAGS = --enable=all --error-exitcode=1

.SUFFIXES: .elf .bin .hex .srec .list .images
.SECONDEXPANSION:
.SECONDARY:

all: $(LIBNAME).a

$(LIBNAME).a: $(OBJS)
	@#printf "  AR      $(subst $(shell pwd)/,,$(@))\n"
	$(AR) $(ARFLAGS) $@ $^ && cp $(LIBNAME).a $(LIBDIR)/.

%.o: %.c Makefile
	@#printf "  CC      $(subst $(shell pwd)/,,$(@))\n"
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.cpp Makefile
	@#printf "  CC      $(subst $(shell pwd)/,,$(@))\n"
	$(CC) $(CFLAGS) -o $@ -c $<

SRC = $(wildcard *.c)
HDR = $(wildcard include/*.h)

style:
	$(STYLER) $(STYLERFLAGS) $(SRC)
	$(STYLER) $(STYLERFLAGS) $(HDR)

clean:
	rm -f *.o
	rm -f *.a
	rm -f *.d
	rm -f *.elf
	rm -f *.bin
	rm -f *.hex
	rm -f *.srec
	rm -f *.list
	rm -f *.orig
	rm -f include/*.orig

.PHONY: images clean

