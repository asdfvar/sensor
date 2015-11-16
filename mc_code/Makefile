BASE = .
CC   = gcc
OBJ  = sensor_main.o example.o
INC  = -I$(BASE)/preprocessing/
LIBPATHS = -L$(BASE)/preprocessing/
LIBS = -lpreproc -lm

EXE = example

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(INC) $(LIBPATHS) $(LIBS)

clean:
	rm $(OBJ) $(EXE)

sensor_main.o: sensor_main.c
	$(CC) $^ -c $(INC)

example.o: example.c
	$(CC) $^ -c $(INC)
