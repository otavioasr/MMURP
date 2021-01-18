#!/bin/bash
g++ ./Sources/*.cpp Main.cpp -o main
 ./main Configs/Config1.csv --iterMax 80 --kMax 1

g++ ./Sources/*.cpp Main.cpp -o main
./main Configs/Config8.csv --iterMax 80 --kMax 5 

g++ ./Sources/*.cpp Main.cpp -o main
 ./main Configs/Config16.csv --iterMax 80 --kMax 9
 
g++ ./Sources/*.cpp Main.cpp -o main
 ./main Configs/Config24.csv  --iterMax 80 --kMax 14 
 
g++ ./Sources/*.cpp Main.cpp -o main
 ./main Configs/Config32.csv --iterMax 80 --kMax 19 
 
g++ ./Sources/*.cpp Main.cpp -o main
 ./main Configs/Config40.csv --iterMax 80 --kMax 24
 
g++ ./Sources/*.cpp Main.cpp -o main
./main Configs/Config48.csv --iterMax 80 --kMax 28

g++ ./Sources/*.cpp Main.cpp -o main
./main Configs/Config56.csv --iterMax 80 --kMax 32

g++ ./Sources/*.cpp Main.cpp -o main
./main Configs/Config64.csv --iterMax 80 --kMax 38

g++ ./Sources/*.cpp Main.cpp -o main
./main Configs/Config72.csv --iterMax 80 --kMax 44

exit 0
