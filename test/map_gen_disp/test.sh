g++ -c ../../src/mapgenrator/randommap.cpp ../../src/mapgenrator/noise.cpp -std=c++11 -I../../include
g++ -c map_gen_test.cpp -lpthread -std=c++11 -I../../include
g++ map_gen_test.o noise.o randommap.o -o map_gtest -L../../lib -lgtest -lpthread -std=c++11
./map_gtest
