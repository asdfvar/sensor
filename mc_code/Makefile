CC = gcc
OBJ = sensor_main.o example.o

EXE = example

all: $(OBJ)
	$(CC) $(OBJ) -o $(EXE)

clean:
	rm $(OBJ) $(EXE)

sensor_main.o: sensor_main.c
	$(CC) $^ -c

example.o: example.c
	$(CC) $^ -c
