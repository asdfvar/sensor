CC = gcc
FLAGS = -O3 -Wall

INC = -I..
LIBS = -lm -lfftw3f

OBJ = test_fft.o fft.o dft_r2c.o

EXE = test

all: $(OBJ)
	$(CC) $(OBJ) $(INC) $(LIBS) -o $(EXE)

clean:
	rm $(OBJ) $(EXE)

test_fft.o: test_fft.c
	$(CC) $^ -c $(FLAGS) $(INC)

fft.o: ../fft.c
	$(CC) $^ -c $(FLAGS) $(INC)

dft_r2c.o: ../dft_r2c.c
	$(CC) $^ -c $(FLAGS) $(INC)
