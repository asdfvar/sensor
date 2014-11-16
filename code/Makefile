CC = gcc
CPPC = g++
FLAGS = -Wall -O3 -lfftw3 -lfftw3f -lm

INC = -Imatchedfilter
LIBPATH = -L./matchedfilter
LIBS = -lmatflt

OBJ = main.o

EXE = main

all: $(OBJ)
	$(CPPC) $(OBJ) $(FLAGS) -o $(EXE) $(INC) $(LIBPATH) $(LIBS)

clean:
	rm $(EXE) $(OBJ)

main.o: main.cpp
	$(CPPC) $^ -c $(INC)
