CPPC = g++
INC = fileio.h ref.h

OBJ = example.o read_reference.o read_kinetisense.o\
      fileio.o

all: $(OBJ)
	$(CPPC) $(OBJ) $(INC) -o exe

%.o: %.cpp
	$(CPPC) $^ -c

clean:
	rm $(OBJ) exe
