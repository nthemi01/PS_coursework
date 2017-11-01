CC = g++
CCFLAGS = -std=c++11\

CIMGFLAGS =\
		  -O2\
		  -L/usr/X11/lib\ # X11 directory varies on different machine
		  -lm\
		  -lpthread\
		  -lX11\
		  -I/usr/X11/include # X11 directory varies on different machine
OBJ = show_image_example.o noise.o randommap.o disdensity.o


show_image_example: $(OBJ)
	$(CC) $(CCFLAGS) $(CIMGFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $(CIMGFLAGS) -o $@ $<

clean:
	rm *.o test
