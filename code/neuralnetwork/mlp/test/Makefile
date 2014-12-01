OBS = ann.o forward.o training.o

FLAGS = -lm -g -Wall
OPT = -O3
INC = -I..

CPPC = g++
EXE = exec

all: example

example: $(OBS) Example.cpp
	$(CPPC) $(OPT) $(OBS) Example.cpp $(INC) $(FLAGS) -o $(EXE)

ann.o: ../ann.cpp
	$(CPPC) $(OPT) $(FLAGS) $^ -c

forward.o: ../forward.cpp
	$(CPPC) $(OPT) $(FLAGS) $^ -c

training.o: ../training.cpp
	$(CPPC) $(OPT) $(FLAGS) $^ -c

clean:
	rm $(EXE) $(OBS) 
