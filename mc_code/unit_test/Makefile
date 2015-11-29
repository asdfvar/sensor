CC  = gcc
CL    = ar rcs
FLAGS = -O3 -Wall

LIBEXE = libtest.a

OBJ = sinwave.o

all: $(OBJ)
	$(CL) $(LIBEXE) $(OBJ)

clean:
	rm $(OBJ) $(LIBEXE)

sinwave.o: sinwave.c
	$(CC) $^ -c $(INC) $(FLAGS)
