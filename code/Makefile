CC = gcc
CPPC = g++
FLAGS = -Wall -O3 -lfftw3 -lfftw3f -lm

INC_x = -L./matchedfilter -I./tools
INC = -I./tools
LIBS = -lmatflt

OBJ = mainwrapper.o data.o fft.o

MATFLT = matchedfilter

EXE = main

all: $(OBJ)
	$(CPPC) $(OBJ) $(FLAGS) $(INC) -o $(EXE)

clean:
	rm $(EXE) $(OBJ)

mainwrapper.o: mainwrapper.cpp
	$(CPPC) $^ -c

data.o: data.cpp
	$(CPPC) $(INC) $^ -c

fft.o: tools/fft.c
	$(CC) $^ -c
