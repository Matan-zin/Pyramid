CC = g++ -std=c++17
CFLAGS = -Wall -g

main: main.o movpoint.o
	$(CC) $(CFLAGS) -o main main.o movpoint.o

main.o: main.cpp movpoint.h shared_data.h
	$(CC) $(CFLAGS) -c main.cpp

movpoint.o: movpoint.cpp movpoint.h
	$(CC) $(CFLAGS) -c movpoint.cpp

valgrind: main
	valgrind ./main