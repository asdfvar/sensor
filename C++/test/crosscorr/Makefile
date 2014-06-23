##########################################
# Makefile to test the cross correlation #
##########################################

CC = gcc
CPPC = g++
FLAGS = -lfftw3 -lfftw3f -lm -O3 -Wall

OBJ = testcrosscorr.o fft.o

EXE = testcrosscorr

all: $(EXE)

$(EXE): $(OBJ)
	$(CPPC) $(OBJ) $(FLAGS) -o $(EXE)

clean:
	rm $(OBJ) $(EXE)

testcrosscorr.o: testcrosscorr.cpp
	$(CPPC) $^ -c

fft.o: fft.c
	$(CC) $^ -c
