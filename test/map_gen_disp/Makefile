CC = g++
CCFLAGS = -std=c++11

CIMGFLAGS =\
		  -O2\
		  -lpthread\
		  -L/usr/X11/lib\
		  -lm\
		  -lpthread\
		  -lX11\
		  -I/usr/X11/include
OBJ = noise.o test.o randommap.o disdensity.o


test: $(OBJ)
	$(CC) $(CCFLAGS) $(CIMGFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CC) -c $(CCFLAGS) $(CIMGFLAGS) -o $@ $<

clean:
	rm *.o test
