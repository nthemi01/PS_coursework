#g++ -c ../src/landscape.cpp -std=c++11
g++ -c test_Neofytos.cpp -lpthread -std=c++11
g++ test_Neofytos.o landscape.o -o test_Neofytos -lgtest -lpthread -std=c++11
./test_Neofytos 
