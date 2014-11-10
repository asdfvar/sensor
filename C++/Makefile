CC = gcc
CPPC = g++
FLAGS = -Wall -O3

INC = -L./matchedfilter
LIBS = -lmatflt

OBJ = mainwrapper.o data.o

MATFLT = matchedfilter

EXE = main

all: $(OBJ)
	$(CPPC) $(OBJ) $(FLAGS) -o $(EXE)

clean:
	rm $(EXE) $(OBJ)

mainwrapper.o: mainwrapper.cpp
	$(CPPC) $^ -c

data.o: data.cpp
	$(CPPC) $^ -c
