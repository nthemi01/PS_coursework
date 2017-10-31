CC = g++
CFLAGS = -std=c++11
OBJ = noise.o test.o randommap.o disdensity.o

test: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.cpp
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm *.o test
