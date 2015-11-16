CC  = gcc
CL    = ar rcs
FLAGS = -O3 -Wall

LIBEXE = libpreproc.a

UTILITIES = ../utilities

INC = -I$(UTILITIES)

OBJ = preproc.o eigen.o

all: $(OBJ)
	$(CL) $(LIBEXE) $(OBJ)

clean:
	rm $(OBJ) $(LIBEXE)

preproc.o: preproc.c
	$(CC) $^ -c $(INC) $(FLAGS)

eigen.o: eigen.c
	$(CC) $^ -c $(INC)
