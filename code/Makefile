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

MAIN_OBJ  = main.o  fft.o
TRAIN_OBJ = train.o fft.o

EXE   = sensor
TRAIN = train

# BUILD ALL

all: $(EXE) $(TRAIN)

$(EXE): $(COMPONENTS) $(MAIN_OBJ)
	cd $(MATCHFILTER) && $(MAKE)
	cd $(PREPROC) && $(MAKE)
	cd $(TOOLS) && $(MAKE)
	$(CPPC) $(MAIN_OBJ) $(FLAGS) -o $(EXE) $(INC) $(LIBPATH) $(LIBS)

$(TRAIN): $(COMPONENTS) $(TRAIN_OBJ)
	cd $(MATCHFILTER) && $(MAKE)
	cd $(PREPROC) && $(MAKE)
	cd $(TOOLS) && $(MAKE)
	$(CPPC) $(TRAIN_OBJ) $(FLAGS) -o $(TRAIN) $(INC) $(LIBPATH) $(LIBS)

# CLEAN ALL

clean:
	make -C $(MATCHFILTER) clean
	make -C $(PREPROC) clean
	make -C $(TOOLS) clean
	rm $(EXE) $(MAIN_OBJ) $(TRAIN_OBJ)

train.o: train.cpp
	$(CPPC) $(MAIN_DIRECTIVE) $^ -c $(INC)

main.o: main.cpp
	$(CPPC) $(MAIN_DIRECTIVE) $^ -c $(INC)

fft.o: tools/fft.c
	$(CC) $^ -c
