g++ -c ../../src/landscape.cpp ../../src/mapgenrator/randommap.cpp ../../src/mapgenrator/noise.cpp -std=c++11
g++ -c map_gen_test.cpp -lpthread -std=c++11
g++ map_gen_test.o landscape.o noise.o randommap.o -o map_gtest -lgtest -lpthread -std=c++11
./map_gtest