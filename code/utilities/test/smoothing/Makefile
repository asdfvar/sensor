CPPC = g++
OBJ = smooth.o apply_filter.o memory_management.o
INC = -I../..

EXE = smooth

all: $(OBJ)
	$(CPPC) $(OBJ) -o $(EXE) $(INC)

clean:
	rm $(OBJ) $(EXE)

smooth.o: smooth.cpp
	$(CPPC) $^ -c $(INC)

apply_filter.o: ../../apply_filter.cpp
	$(CPPC) $^ -c $(INC)

memory_management.o: ../../memory_management.cpp
	$(CPPC) $^ -c $(INC)
