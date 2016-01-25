CC = gcc
CL = ar rcs
FLAGS = -O3 -Wall

LIB = libfft.a

OBJ = dft_r2c.o idft_c2r.o idft_c2c.o local_fft_r2c.o local_fft_wrapper_r2c.o \
      local_ifft_c2r.o local_ifft_c2c.o local_ifft_wrapper_c2r.o local_trig.o \
      get_element_conj_sym.o

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

idft_c2c.o: idft_c2c.c
	$(CC) $^ -c $(FLAGS)

local_fft_r2c.o: local_fft_r2c.c
	$(CC) $^ -c $(FLAGS)

local_fft_wrapper_r2c.o: local_fft_wrapper_r2c.c
	$(CC) $^ -c $(FLAGS)

local_ifft_c2r.o: local_ifft_c2r.c
	$(CC) $^ -c $(FLAGS)

local_ifft_c2c.o: local_ifft_c2c.c
	$(CC) $^ -c $(FLAGS)

local_ifft_wrapper_c2r.o: local_ifft_wrapper_c2r.c
	$(CC) $^ -c $(FLAGS)

local_trig.o: local_trig.c
	$(CC) $^ -c $(FLAGS)

get_element_conj_sym.o: get_element_conj_sym.c
	$(CC) $^ -c $(FLAGS)
