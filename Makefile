CC = g++

SRCDIR = $(PS_PROJ_HOME)/src

TESTDIR = $(PS_PROJ_HOME)/test
				  
INSTDIR = $(HOME)/PScourse1

OBJDIR = $(PS_PROJ_HOME)/build/obj

BINDIR = $(PS_PROJ_HOME)/build/bin

TESTBINDIR = $(PS_PROJ_HOME)/build/testbin

INCLUDEDIR = $(PS_PROJ_HOME)/include

CCFLAGS = -std=c++11\
                  -I$(PS_PROJ_HOME)/include\

GTESTFLAG = -lgtest \
				  
LIB = \
          -L$(PS_PROJ_HOME)/lib\
          -L/usr/X11/lib\
          -lm\
          -lX11\
          -lpthread

OBJS = $(OBJDIR)/*.o  

all:product test

product:$(BINDIR)/caldensity
	echo Product program compile done.

$(BINDIR)/caldensity: $(OBJDIR)/caldensity.o $(OBJDIR)/landscape.o $(OBJDIR)/disdensity.o
	$(CC) $(CCFLAGS) $(LIB) -O3 -o $@ $^

$(OBJDIR)/caldensity.o: $(SRCDIR)/caldensity.cpp
	$(CC) -c $(CCFLAGS) $(LIB)  -o $@ $<

$(OBJDIR)/landscape.o: $(SRCDIR)/landscape.cpp $(INCLUDEDIR)/landscape.h
	$(CC) -c $(CCFLAGS) $(LIB)  -o $@ $<

$(OBJDIR)/disdensity.o: $(SRCDIR)/disdensity.cpp $(INCLUDEDIR)/disdensity.h
	$(CC) -c $(CCFLAGS) $(LIB)  -o $@ $<

		
clean:
	rm $(OBJDIR)/*
	rm $(BINDIR)/*
	rm $(TESTBINDIR)/*
	echo done!

install: 
	rm -r $(INSTDIR) 2 > /dev/null
	mkdir $(INSTDIR)
	mkdir $(INSTDIR)/bin/
	mkdir $(INSTDIR)/cfg/
	cp $(BINDIR)/* $(INSTDIR)
	cp $(PS_PROJ_HOME)/cfg/* $(INSTDIR)/cfg/
	echo done!

