CC = gcc
FLAGS = -O3 -Wall

INC = -I..
LIBS = -lm -lfftw3f

OBJ_FFT = test_fft.o fft.o dft_r2c.o fft_front_r2c.o fft_l_r2c.o \
          gettime.o
OBJ_TRIG = test_trig.o local_trig.o

EXE_FFT = test_fft
EXE_TRIG = test_trig

all: FFT_TEST TRIG_TEST

TRIG_TEST: $(OBJ_TRIG)
	$(CC) $(OBJ_TRIG) $(INC) $(LIBS) -o $(EXE_TRIG)

FFT_TEST: $(OBJ_FFT)
	$(CC) $(OBJ_FFT) $(INC) $(LIBS) -o $(EXE_FFT)

clean:
	rm $(OBJ_FFT) $(OBJ_TRIG) $(EXE_FFT) $(EXE_TRIG)

test_fft.o: test_fft.c
	$(CC) $^ -c $(FLAGS) $(INC)

fft.o: ../fft.c
	$(CC) $^ -c $(FLAGS) $(INC)

dft_r2c.o: ../dft_r2c.c
	$(CC) $^ -c $(FLAGS) $(INC)

fft_l_r2c.o: ../fft_l_r2c.c
	$(CC) $^ -c $(FLAGS) $(INC)

fft_front_r2c.o: ../fft_front_r2c.c
	$(CC) $^ -c $(FLAGS) $(INC)

gettime.o: gettime.c
	$(CC) $^ -c $(FLAGS) $(INC)

test_trig.o: test_trig.c
	$(CC) $^ -c $(FLAGS) $(INC)

local_trig.o: ../local_trig.c
	$(CC) $^ -c $(FLAGS) $(INC)
