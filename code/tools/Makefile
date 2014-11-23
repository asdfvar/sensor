CC = gcc
CPPC = g++
CL = ar rcs

LIB = libsens.a

OBJ = mflt.o fft.o read_kinetisense.o

all: $(OBJ)
	$(CL) $(LIB) $(OBJ)

clean:
	rm $(OBJ) $(LIB)

mflt.o: mflt.cpp
	$(CPPC) $^ -c

fft.o: fft.c
	$(CC) $^ -c

read_kinetisense.o: read_kinetisense.cpp
	$(CC) $^ -c
