CC = gcc
CPPC = g++
CL = ar rcs

LIB = libsens.a

OBJ = fft.o read_kinetisense.o fileio.o gettime.o

all: $(OBJ)
	$(CL) $(LIB) $(OBJ)

clean:
	rm $(OBJ) $(LIB)

fft.o: fft.c
	$(CC) $^ -c

read_kinetisense.o: read_kinetisense.cpp
	$(CPPC) $^ -c

fileio.o: fileio.cpp
	$(CPPC) $^ -c

gettime.o: gettime.cpp
	$(CPPC) $^ -c
