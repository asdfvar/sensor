CPPC = g++
OBJ = smooth.o filter.o memory_management.o
INC = -I../..

EXE = smooth

all: $(OBJ)
	$(CPPC) $(OBJ) -o $(EXE) $(INC)

clean:
	rm $(OBJ) $(EXE)

smooth.o: smooth.cpp
	$(CPPC) $^ -c $(INC)

filter.o: ../../filter.cpp
	$(CPPC) $^ -c $(INC)

memory_management.o: ../../memory_management.cpp
	$(CPPC) $^ -c $(INC)
