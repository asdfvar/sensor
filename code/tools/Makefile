CC = gcc
CPPC = g++
CL = ar rcs

LIB = libsens.a

OBJ = mflt.o fft.o

all: $(OBJ)
	$(CL) $(LIB) $(OBJ)

mflt.o: mflt.cpp
	$(CPPC) $^ -c

fft.o: fft.c
	$(CPPC) $^ -c

clean:
	rm $(OBJ) $(LIB)
