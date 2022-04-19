CC = gcc
CFLAGS = -g -no-pie -O3 -Wall -mavx2

SrcDir = src
BinDir = bin

objects = $(BinDir)/List.o $(BinDir)/HashT.o $(BinDir)/main.o $(BinDir)/H5.o

HashTT: List.o HashT.o main.o H5.o
	$(CC) $(CFLAGS) -o HashTT $(objects)

List.o: $(SrcDir)/List.c $(SrcDir)/List.h
	$(CC) -c $(CFLAGS) $< -o $(BinDir)/$@

HashT.o: $(SrcDir)/HashT.c $(SrcDir)/HashT.h
	$(CC) -c $(CFLAGS) $< -o $(BinDir)/$@

main.o: $(SrcDir)/main.c $(SrcDir)/main.h
	$(CC) -c $(CFLAGS) $< -o $(BinDir)/$@

H5.o: $(SrcDir)/H5.s
	nasm -felf64 $< -o $(BinDir)/$@

create:
	mkdir bin

clean:
	rm HashTT $(objects)
	rmdir $(BinDir)
