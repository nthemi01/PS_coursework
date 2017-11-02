CC = g++
CCFLAGS = -std=c++11\
		  -I../../include\
		  -L../../lib

# X11 directory varies on different machine
CIMGFLAGS =\
		  -L/usr/X11/lib\
		  -I/usr/X11/include

LIB = \
	  -lm\
	  -lX11\
	  -lpthread

GTESTFLAG = -lgtest\
			-D GTEST

IMSHOW_OBJ = show_image_example.o noise.o randommap.o disdensity.o
MAPGEN_OBJ = map_gen_example.o noise.o randommap.o disdensity.o

all:show_image_example map_gen_example

show_image_example: $(IMSHOW_OBJ)
	$(CC) $(CCFLAGS) $(CIMGFLAGS) $(LIB) -O3 -o $@ $^

map_gen_example: $(MAPGEN_OBJ)
	$(CC) $(CCFLAGS) $(CIMGFLAGS) $(LIB) -O3 -o $@ $^

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $(CIMGFLAGS) -o $@ $<

test: show_image_test map_gen_test

show_image_test:$(IMSHOW_OBJ)
	$(CC) $(CCFLAGS) $(CIMGFLAGS) $(LIB) $(GTESTFLAG) -o $@ $^

map_gen_test:$(MAPGEN_OBJ)
	$(CC) $(CCFLAGS) $(CIMGFLAGS) $(LIB) $(GTESTFLAG) -o $@ $^

clean:
	rm *.o *.ppm *.dat show_image_example map_gen_example show_image_test map_gen_test
