CC = gcc
CFLAGS = -g -Wall -mavx2 -msse4.1

SrcDir = src
BinDir = bin

objects = $(BinDir)/List.o $(BinDir)/HashT.o $(BinDir)/main.o

HashTT: List.o HashT.o main.o
	$(CC) $(CFLAGS) -o HashTT $(objects)

List.o: $(SrcDir)/List.c $(SrcDir)/List.h
	$(CC) -c $(CFLAGS) $< -o $(BinDir)/$@

HashT.o: $(SrcDir)/HashT.c $(SrcDir)/HashT.h
	$(CC) -c $(CFLAGS) $< -o $(BinDir)/$@

main.o: $(SrcDir)/main.c $(SrcDir)/main.h
	$(CC) -c $(CFLAGS) $< -o $(BinDir)/$@

create:
	mkdir bin

clean:
	rm HashTT $(objects)
	rmdir $(BinDir)
