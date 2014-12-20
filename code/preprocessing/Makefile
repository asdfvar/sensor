CPPC = g++
CL = ar rcs

LIBEXE = libpreproc.a

TOOLS = ../tools

INC = -I$(TOOLS)

OBJ = preproc.o eigen.o

all: $(OBJ)
	$(CL) $(LIBEXE) $(OBJ)

clean:
	rm $(OBJ) $(LIBEXE)

preproc.o: preproc.cpp
	$(CPPC) $^ -c $(INC)

eigen.o: eigen.cpp
	$(CPPC) $^ -c $(INC)
