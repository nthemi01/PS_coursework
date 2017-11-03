CC = g++
CCFLAGS = -std=c++11\
		  -I../../include\

SRC_DIR = ../../src

# X11 directory varies on different machine
# sometimes they are inside the default include and lib directory
CIMGFLAGS =\
		  -I/usr/X11/include

LIB = \
	  -L../../lib\
	  -L/usr/X11/lib\
	  -lm\
	  -lX11\
	  -lpthread

#GTESTFLAG = -lgtest\
#			-DGTEST

IMSHOW_OBJ = show_image_example.o noise.o randommap.o disdensity.o
MAPGEN_OBJ = map_gen_example.o noise.o randommap.o disdensity.o
#CALC_OBJ = caldensity.o landscape.o disdensity.o randommap.o noise.o

all:show_image_example map_gen_example

show_image_example: $(IMSHOW_OBJ)
	$(CC) $(CCFLAGS) $(CIMGFLAGS) $(LIB) -O3 -o $@ $^

map_gen_example: $(MAPGEN_OBJ)
	$(CC) $(CCFLAGS) $(CIMGFLAGS) $(LIB) -O3 -o $@ $^

%.o:%.cpp
	$(CC) -c $(CCFLAGS) $(CIMGFLAGS) -o $@ $<

%.o: $(SRC_DIR)/mapgenrator/%.cpp
	$(CC) -c $(CCFLAGS) -o $@ $<

%.o: $(SRC_DIR)/disdensity/%.cpp
	$(CC) -c $(CCFLAGS) $(CIMGFLAGS) -o $@ $<

landscape.o:$(SRC_DIR)/landscape.cpp
	$(CC) -c $(CCFLAGS) $(CIMGFLAGS) -o $@ $<

#calc:$(CALC_OBJ)
#	$(CC) $(CCFLAGS) $(CIMGFLAGS) $(LIB) -DDEBUG_OUT -O3 -o $@ $^

#caldensity.o:$(SRC_DIR)/caldensity.cpp
#		$(CC) -c $(CCFLAGS) $(CIMGFLAGS) -o $@ $<

clean:
	rm *.o *.ppm *.dat show_image_example map_gen_example show_image_test map_gen_test
