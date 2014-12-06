CPPC = g++
FLAG = -O3 -Wall

OBJ = eigen.o example.o

all: $(OBJ)
	$(CPPC) $(FLAG) $(OBJ) -o exe

clean:
	rm $(OBJ) exe

%.o: %.cpp
	$(CPPC) $^ -c
