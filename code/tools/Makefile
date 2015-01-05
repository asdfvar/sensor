CC = gcc
CPPC = g++
CL = ar rcs
FLAGS = -O3 -Wall

LIB = libsens.a

OBJ = fft.o read_kinetisense.o fileio.o gettime.o read_file_paths.o

all: $(OBJ)
	$(CL) $(LIB) $(OBJ)

clean:
	rm $(OBJ) $(LIB)

fft.o: fft.c
	$(CC) $^ -c $(FLAGS)

read_kinetisense.o: read_kinetisense.cpp
	$(CPPC) $^ -c $(FLAGS)

fileio.o: fileio.cpp
	$(CPPC) $^ -c $(FLAGS)

gettime.o: gettime.cpp
	$(CPPC) $^ -c $(FLAGS)

read_file_paths.o: read_file_paths.cpp
	$(CPPC) $^ -c $(FLAGS)
