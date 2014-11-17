CC = gcc
CPPC = g++
FLAGS = -Wall -O3 -lfftw3 -lfftw3f -lm

MATCHFILTER = matchedfilter
TOOLS = tools

INC = -I$(MATCHFILTER) -I$(TOOLS)
LIBPATH = -L./$(MATCHFILTER) -L./$(TOOLS)
LIBS = -lmatflt -lsens

OBJ = main.o

EXE = main

all: $(OBJ)
	cd $(MATCHFILTER) && $(MAKE)
	cd $(TOOLS) && $(MAKE)
	$(CPPC) $(OBJ) $(FLAGS) -o $(EXE) $(INC) $(LIBPATH) $(LIBS)

clean:
	make -C $(MATCHFILTER) clean
	make -C $(TOOLS) clean
	rm $(EXE) $(OBJ)

main.o: main.cpp
	$(CPPC) $^ -c $(INC)
