CC = gcc
FLAGS = -O3 -Wall

INC = -I..
LIBS = -lm -lfftw3f

OBJ_FFT = test_fft.o fft.o idft_c2r.o idft_c2c.o dft_r2c.o local_fft_wrapper_r2c.o local_fft_r2c.o \
          local_ifft_wrapper_c2r.o local_ifft_c2r.o \
          local_ifft_c2c.o gettime.o get_element.o
OBJ_TRIG = test_trig.o
OBJ_SHARED = local_trig.o

EXE_FFT = test_fft
EXE_TRIG = test_trig

all: FFT_TEST TRIG_TEST

TRIG_TEST: $(OBJ_TRIG) $(OBJ_SHARED)
	$(CC) $(OBJ_TRIG) $(OBJ_SHARED) $(INC) $(LIBS) -o $(EXE_TRIG)

FFT_TEST: $(OBJ_FFT) $(OBJ_SHARED) $(OBJ_SHARED)
	$(CC) $(OBJ_FFT) $(INC) $(LIBS) -o $(EXE_FFT)

clean:
	rm $(OBJ_FFT) $(OBJ_TRIG) $(OBJ_SHARED) $(EXE_FFT) $(EXE_TRIG)

test_fft.o: test_fft.c
	$(CC) $^ -c $(FLAGS) $(INC)

fft.o: ../fft.c
	$(CC) $^ -c $(FLAGS) $(INC)

dft_r2c.o: ../dft_r2c.c
	$(CC) $^ -c $(FLAGS) $(INC)

idft_c2r.o: ../idft_c2r.c
	$(CC) $^ -c $(FLAGS) $(INC)

idft_c2c.o: ../idft_c2c.c
	$(CC) $^ -c $(FLAGS) $(INC)

local_fft_r2c.o: ../local_fft_r2c.c
	$(CC) $^ -c $(FLAGS) $(INC)

local_fft_wrapper_r2c.o: ../local_fft_wrapper_r2c.c
	$(CC) $^ -c $(FLAGS) $(INC)

local_ifft_c2r.o: ../local_ifft_c2r.c
	$(CC) $^ -c $(FLAGS) $(INC)

local_ifft_wrapper_c2r.o: ../local_ifft_wrapper_c2r.c
	$(CC) $^ -c $(FLAGS) $(INC)

local_ifft_c2c.o: ../local_ifft_c2c.c
	$(CC) $^ -c $(FLAGS) $(INC)

gettime.o: gettime.c
	$(CC) $^ -c $(FLAGS) $(INC)

test_trig.o: test_trig.c
	$(CC) $^ -c $(FLAGS) $(INC)

local_trig.o: ../local_trig.c
	$(CC) $^ -c $(FLAGS) $(INC)

get_element.o: ../get_element.c
	$(CC) $^ -c $(FLAGS) $(INC)
