CC = gcc
CPPC = g++
CL = ar rcs
FLAGS = -O3 -Wall

LIB = libutils.a

OBJ = energy_expenditure.o

all: $(OBJ)
	$(CL) $(LIB) $(OBJ)

clean:
	rm $(OBJ) $(LIB)

energy_expenditure.o: energy_expenditure.c
	$(CC) $^ -c $(FLAGS)
