CC = gcc
FLAGS = -O3 -Wall

INC = -I..
LIBS = -lm

OBJ = test_qmath.o

DEFS = -DPC

EXE = test_qmath

all: QMATH_TEST

QMATH_TEST: $(OBJ)
	$(CC) $(OBJ) $(INC) $(LIBS) -o $(EXE)

clean:
	rm $(OBJ) $(EXE)

test_qmath.o: test_qmath.c
	$(CC) $^ $(DEFS) -c $(FLAGS) $(INC)
