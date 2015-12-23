CC = gcc
CL = ar rcs
FLAGS = -O3 -Wall

LIB = libfft.a

OBJ = fft.o dft_r2c.o

all: $(OBJ)
	$(CL) $(LIB) $(OBJ)

clean:
	rm $(OBJ) $(LIB)

fft.o: fft.c
	$(CC) $^ -c $(FLAGS)

dft_r2c.o: dft_r2c.c
	$(CC) $^ -c $(FLAGS)
