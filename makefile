
CC = g++
CFLAGS = -g -O -Wall
BIN = mazemake mazesolve mazeshow
OBJ = $(BIN:%=%.o) mazegrid.o dset.o support.o

all: $(OBJ) $(BIN) 

mazemake: mazemake.o mazegrid.o dset.o dset.h dset.cpp mazegrid.h mazegrid.cpp
	$(CC) $(CFLAGS) -o mazemake mazemake.o mazegrid.o dset.o

mazesolve: mazesolve.o mazegrid.o dset.o dset.h dset.cpp mazegrid.h mazegrid.cpp
	$(CC) $(CFLAGS) -o mazesolve mazesolve.o mazegrid.o dset.o

mazeshow: mazeshow.o support.h matrix.h support.cpp
	$(CC) $(CFLAGS) -o mazeshow mazeshow.o support.o

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $<

clean:
	@rm -f $(BIN) $(OBJ) 
	# uncomment next line to remove mazes
	@rm -f [mp]*.txt [mp]*.ppm [mp]*.png
