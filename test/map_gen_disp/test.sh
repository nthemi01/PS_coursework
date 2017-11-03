<<<<<<< HEAD
g++ -c  ../../src/mapgenrator/randommap.cpp ../../src/mapgenrator/noise.cpp -std=c++11
g++ -c map_gen_test.cpp -lpthread -std=c++11
g++ map_gen_test.o noise.o randommap.o -o map_gtest -lgtest -lpthread -std=c++11
=======
g++ -c ../../src/landscape.cpp ../../src/mapgenrator/randommap.cpp ../../src/mapgenrator/noise.cpp -std=c++11 -I../../include
g++ -c map_gen_test.cpp -lpthread -std=c++11 -I../../include
g++ map_gen_test.o landscape.o noise.o randommap.o -o map_gtest -lgtest -lpthread -std=c++11
>>>>>>> 4d4ec1fee899a2eaac86846bc9cde71b9f5fe0e1
./map_gtest
