CC = g++

PS_PROJ_HOME = .

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

CIMGINC = -I/usr/X11/include

LIB = \
          -L$(PS_PROJ_HOME)/lib\
          -L/usr/X11/lib\
          -lm\
          -lX11\
          -lpthread

OBJS = $(OBJDIR)/caldensity.o\
	   $(OBJDIR)/landscape.o\
	   $(OBJDIR)/disdensity.o\
	   $(OBJDIR)/randommap.o\
	   $(OBJDIR)/noise.o
SRC := $(wildcard $(TESTDIR)/*.cpp)
DIR:=$(notdir $(SRC))
OBJ:=$(patsubst %.cpp,%.o,$(DIR) )
EXEC:=$(patsubst %.cpp,%,$(DIR))

all:product
	@echo ------------------------------------------------------
	@echo         Compiling work finished
	@echo ------------------------------------------------------

product:$(BINDIR)/caldensity
	@echo ------------------------------------------------------
	@echo Production program generated.
$(BINDIR)/caldensity: $(OBJS)
	@echo ------------------------------------------------------
	@echo Compiling $@ 
	@echo from $^......
	@$(CC) $(CCFLAGS) $(LIB) -O3 -o $@ $^

$(OBJDIR)/caldensity.o: $(SRCDIR)/caldensity.cpp
	@echo ------------------------------------------------------
	@echo Compiling $@
	@echo from $^......
	@$(CC) -c $(CCFLAGS) $(LIB) $(CIMGINC) -o $@ $<

$(OBJDIR)/landscape.o: $(SRCDIR)/landscape.cpp $(INCLUDEDIR)/landscape.h
	@echo ------------------------------------------------------
	@echo Compiling $@
	@echo from $^......
	@$(CC) -c $(CCFLAGS) $(LIB)  -o $@ $<

$(OBJDIR)/disdensity.o: $(SRCDIR)/disdensity.cpp $(INCLUDEDIR)/disdensity.h
	@echo ------------------------------------------------------
	@echo Compiling $@
	@echo from $^......
	@$(CC) -c $(CCFLAGS) $(LIB) $(CIMGINC) -o $@ $<

$(OBJDIR)/%.o: $(SRCDIR)/mapgenrator/%.cpp  $(INCLUDEDIR)/%.h
	@echo ------------------------------------------------------
	@echo Compiling $@
	@echo from $<......
	@$(CC) -c $(CCFLAGS) $(LIB) -o $@ $<


.PHONY: test
test:product
	@echo ------------------------------------------------------
	@echo Unitest files compiling......
	@for name in $(EXEC) ;\
	do \
		$(CC) -c $(CCFLAGS) $(LIB) $(TESTDIR)/$$name.cpp 1>/dev/null;\
		$(CC) $$name.o $(OBJDIR)/landscape.o $(OBJDIR)/noise.o $(OBJDIR)/randommap.o $(CCFLAGS) $(LIB) $(GTESTFLAG) -o $$name.out  1>/dev/null; \
	done
	@rm -f *.o
	@mkdir $(TESTBINDIR)
	@mv *.out $(TESTBINDIR)/
	@cp ./test/*.dat $(TESTBINDIR)/
	@echo done!
	@echo ------------------------------------------------------
	@echo
	@echo  Executing unitests......
	@echo 
	@echo //////////////////////////////////////////////////////
	@for files in `ls $(TESTBINDIR)` ;\
	do \
	  if [ "$${files##*.}" = "out" ] ; \
	  then  \
	    ./$(TESTBINDIR)/$$files ; \
	  fi \
	done
	@echo ------------------------------------------------------


.PHONY: clean
clean : 
	@echo ------------------------------------------------------
	@echo System cleaning......
	@rm -f $(OBJDIR)/* 
	@rm -f $(BINDIR)/* 
	@rm -f $(TESTBINDIR)/* 
	@echo done!
	@echo ------------------------------------------------------

.PHONY: install
install: product 
	@echo ------------------------------------------------------
	@echo System installing......
	@rm -r -f $(INSTDIR)
	@-mkdir $(INSTDIR) 
	@-mkdir $(INSTDIR)/bin
	@-mkdir $(INSTDIR)/cfg
	@cp $(BINDIR)/* $(INSTDIR)/bin
	@cp $(PS_PROJ_HOME)/cfg/* $(INSTDIR)/cfg
	@echo done! System is at $(HOME)/PScourse1 
	@echo ------------------------------------------------------

