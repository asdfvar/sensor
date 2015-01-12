CC = gcc
CPPC = g++
FLAGS = -Wall -O3 -lfftw3f -lm

MATCHFILTER = matchedfilter
PREPROC = preprocessing
TOOLS = tools

INC = -I$(MATCHFILTER) -I$(TOOLS) -I$(PREPROC)
LIBPATH = -L./$(MATCHFILTER) -L./$(TOOLS) -L./$(PREPROC)

LIBS = -lmatflt -lsens -lpreproc

# DIRECTIVE
# switch between PC and onboard hardware

MAIN_DIRECTIVE = -Dpc

OBJ = main.o fft.o

EXE = sensor

# BUILD ALL

all: $(OBJ)
	cd $(MATCHFILTER) && $(MAKE)
	cd $(PREPROC) && $(MAKE)
	cd $(TOOLS) && $(MAKE)
	$(CPPC) $(OBJ) $(FLAGS) -o $(EXE) $(INC) $(LIBPATH) $(LIBS)

# CLEAN ALL

clean:
	make -C $(MATCHFILTER) clean
	make -C $(PREPROC) clean
	make -C $(TOOLS) clean
	rm $(EXE) $(OBJ)

main.o: main.cpp
	$(CPPC) $(MAIN_DIRECTIVE) $^ -c $(INC)

fft.o: tools/fft.c
	$(CC) $^ -c
