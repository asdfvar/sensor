CC = gcc
CPPC = g++
CL = ar rcs
FLAGS = -O3 -Wall

LIB = libsens.a

OBJ = fft.o read_kinetisense.o fileio.o gettime.o write_data.o \
      taper.o energy_expenditure.o

all: $(OBJ)
	$(CL) $(LIB) $(OBJ)

clean:
	rm $(OBJ) $(LIB)

fft.o: fft.c
	$(CC) $^ -c $(FLAGS)

read_kinetisense.o: read_kinetisense.cpp
	$(CPPC) $^ -c $(FLAGS)

fileio.o: fileio.cpp
	$(CPPC) $^ -c $(FLAGS)

gettime.o: gettime.cpp
	$(CPPC) $^ -c $(FLAGS)

write_data.o: write_data.cpp
	$(CPPC) $^ -c $(FLAGS)

taper.o: taper.cpp
	$(CPPC) $^ -c $(FLAGS)

energy_expenditure.o: energy_expenditure.cpp
	$(CPPC) $^ -c $(FLAGS)
