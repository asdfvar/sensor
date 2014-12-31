CC = gcc
CPPC = g++
CL = ar rcs

LIB = libsens.a

OBJ = fft.o read_kinetisense.o read_reference.o\
      fileio.o

all: $(OBJ)
	$(CL) $(LIB) $(OBJ)

clean:
	rm $(OBJ) $(LIB)

fft.o: fft.c
	$(CC) $^ -c

read_kinetisense.o: read_kinetisense.cpp
	$(CPPC) $^ -c

read_reference.o: read_reference.cpp
	$(CPPC) $^ -c

fileio.o: fileio.cpp
	$(CPPC) $^ -c
