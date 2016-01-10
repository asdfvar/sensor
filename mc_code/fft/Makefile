CC = gcc
CL = ar rcs
FLAGS = -O3 -Wall

LIB = libfft.a

OBJ = dft_r2c.o idft_c2r.o local_fft_r2c.o local_fft_wrapper_r2c.o local_trig.o

all: $(OBJ)
	$(CL) $(LIB) $(OBJ)

clean:
	rm $(OBJ) $(LIB)

fft.o: fft.c
	$(CC) $^ -c $(FLAGS)

dft_r2c.o: dft_r2c.c
	$(CC) $^ -c $(FLAGS)

idft_r2c.o: idft_r2c.c
	$(CC) $^ -c $(FLAGS)

local_fft_r2c.o: local_fft_r2c.c
	$(CC) $^ -c $(FLAGS)

local_fft_wrapper_r2c.o: local_fft_wrapper_r2c.c
	$(CC) $^ -c $(FLAGS)

local_trig.o: local_trig.c
	$(CC) $^ -c $(FLAGS)
