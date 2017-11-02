g++ -c ../src/landscape.cpp
g++ -c conor_test.cpp -lpthread
g++ conor_test.o landscape.o -o cftest1 -lgtest -lpthread
./cftest1