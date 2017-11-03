CC = g++
CCFLAGS = -std=c++11\


SRC_DIR = ../../src

# X11 directory varies on different machine
# sometimes they are inside the default include and lib directory
CIMGINC =\
		  -I/usr/X11/include
INC =\
	 -I../../include

LIB = \
	  -L../../lib\
	  -L/usr/X11/lib\
	  -lm\
	  -lX11\
	  -lpthread


IMSHOW_OBJ = show_image_example.o noise.o randommap.o disdensity.o
MAPGEN_OBJ = map_gen_example.o noise.o randommap.o disdensity.o
CALC_OBJ = caldensity.o noise.o randommap.o disdensity.o landscape.o

EXEC = show_image_example map_gen_example

all: $(EXEC)

show_image_example: $(IMSHOW_OBJ)
	$(CC) $(CCFLAGS) $(LIB) -O3 -o $@ $^

map_gen_example: $(MAPGEN_OBJ)
	$(CC) $(CCFLAGS) $(LIB) -O3 -o $@ $^

%.o:%.cpp
	$(CC) -c $(CCFLAGS) $(INC) $(CIMGINC) -o $@ $<

%.o: $(SRC_DIR)/mapgenrator/%.cpp
	$(CC) -c $(CCFLAGS) $(INC) -o $@ $<

disdensity.o: $(SRC_DIR)/disdensity.cpp
	$(CC) -c $(CCFLAGS) $(INC) $(CIMGINC) -o $@ $<

landscape.o:$(SRC_DIR)/landscape.cpp
	$(CC) -c $(CCFLAGS) $(INC) $(CIMGINC) -o $@ $<

calc:$(CALC_OBJ)
	$(CC) $(CCFLAGS) $(LIB) -DDEBUG_OUT -O3 -o $@ $^

caldensity.o:$(SRC_DIR)/caldensity.cpp
		$(CC) -c $(CCFLAGS) $(CIMGINC) $(INC) -o $@ $<


.PHONY:clean
clean:
	rm *.o *.ppm *.dat show_image_example map_gen_example
