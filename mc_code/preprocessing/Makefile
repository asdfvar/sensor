CC  = gcc
CL    = ar rcs
FLAGS = -O3 -Wall

LIBEXE = libpreproc.a

UTILITIES = ../utilities

INC = -I$(UTILITIES)

OBJ = preproc.o eigen.o filter.o down_sample.o

all: $(OBJ)
	$(CL) $(LIBEXE) $(OBJ)

clean:
	rm $(OBJ) $(LIBEXE)

preproc.o: preproc.c
	$(CC) $^ -c $(INC) $(FLAGS)

eigen.o: eigen.c
	$(CC) $^ -c $(INC)

filter.o: filter.c
	$(CC) $^ -c $(INC) $(FLAGS)

down_sample.o: down_sample.c
	$(CC) $^ -c $(INC) $(FLAGS)
