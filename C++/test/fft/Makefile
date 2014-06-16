############################
# Makefile to test the fft #
############################

CC = gcc
CPPC = g++

FLAGS = -lfftw3 -lfftw3f -lm -Wall

OBJ = testfft.o fft.o

EXE = testfft

all: $(EXE)

$(EXE): $(OBJ)
	$(CPPC) $(OBJ) $(FLAGS) -o $(EXE)

clean:
	rm $(OBJ) $(EXE)

fft.o: fft.c
	$(CC) $^ -c

testfft.o: testfft.cpp
	$(CPPC) $^ -c
