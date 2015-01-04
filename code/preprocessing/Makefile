CPPC = g++
CL = ar rcs
FLAGS = -O3 -Wall

LIBEXE = libpreproc.a

TOOLS = ../tools

INC = -I$(TOOLS)

OBJ = preproc.o eigen.o

all: $(OBJ)
	$(CL) $(LIBEXE) $(OBJ)

clean:
	rm $(OBJ) $(LIBEXE)

preproc.o: preproc.cpp
	$(CPPC) $^ -c $(INC) $(FLAGS)

eigen.o: eigen.cpp
	$(CPPC) $^ -c $(INC)
