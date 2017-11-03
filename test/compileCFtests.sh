g++ -c ../src/landscape.cpp ../src/mapgenrator/randommap.cpp ../src/mapgenrator/noise.cpp -std=c++11
g++ -c conor_test.cpp -lpthread -std=c++11
g++ conor_test.o landscape.o noise.o randommap.o -o cftest1 -lgtest -lpthread -std=c++11
./cftest1