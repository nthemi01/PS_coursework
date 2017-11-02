CC = g++
CCFLAGS = -std=c++11\

# X11 directory varies on different machine

CIMGFLAGS =\
		  -O2\
		  -L/usr/X11/lib\
		  -lm\
		  -lpthread\
		  -lX11\
		  -I/usr/X11/include
IMSHOW_OBJ = show_image_example.o noise.o randommap.o disdensity.o
MAPGEN_OBJ = map_gen_example.o noise.o randommap.o disdensity.o

all:show_image_example map_gen_example

show_image_example: $(IMSHOW_OBJ)
	$(CC) $(CCFLAGS) $(CIMGFLAGS) -o $@ $(IMSHOW_OBJ)

map_gen_example: $(MAPGEN_OBJ)
	$(CC) $(CCFLAGS) $(CIMGFLAGS) -o $@ $(MAPGEN_OBJ)

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $(CIMGFLAGS) -o $@ $<

clean:
	rm *.o *.ppm *.dat
	rm show_image_example map_gen_example
