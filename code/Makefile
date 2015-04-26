CC = gcc
CPPC = g++
FLAGS = -Wall -O3 -lfftw3f -lm

MATCHFILTER = matchedfilter
PREPROC = preprocessing
TOOLS = tools

INC = -I$(MATCHFILTER) -I$(TOOLS) -I$(PREPROC)
LIBPATH = -L./$(MATCHFILTER) -L./$(TOOLS) -L./$(PREPROC)

LIBS = -lmatflt -lsens -lpreproc

MAIN_DIRECTIVE = -Dpc #-DTAPER

MAIN_OBJ  = main.o
TRAIN_OBJ = train.o
FFT_OBJ   = fft.o

EXE   = sensor
TRAIN = train

# BUILD ALL

all: $(EXE) $(TRAIN)

$(EXE): $(MAIN_OBJ) $(FFT_OBJ)
	cd $(MATCHFILTER) && $(MAKE)
	cd $(PREPROC) && $(MAKE)
	cd $(TOOLS) && $(MAKE)
	$(CPPC) $(MAIN_OBJ) $(FFT_OBJ) $(FLAGS) -o $(EXE) $(INC) $(LIBPATH) $(LIBS)

$(TRAIN): $(TRAIN_OBJ) $(FFT_OBJ)
	cd $(MATCHFILTER) && $(MAKE)
	cd $(PREPROC) && $(MAKE)
	cd $(TOOLS) && $(MAKE)
	$(CPPC) $(TRAIN_OBJ) $(FFT_OBJ) $(FLAGS) -o $(TRAIN) $(INC) $(LIBPATH) $(LIBS)

# CLEAN ALL

clean:
	make -C $(MATCHFILTER) clean
	make -C $(PREPROC) clean
	make -C $(TOOLS) clean
	rm $(EXE) $(TRAIN) $(MAIN_OBJ) $(FFT_OBJ) $(TRAIN_OBJ)

train.o: train.cpp
	$(CPPC) $(MAIN_DIRECTIVE) $^ -c $(INC)

main.o: main.cpp
	$(CPPC) $(MAIN_DIRECTIVE) $^ -c $(INC)

fft.o: tools/fft.c
	$(CC) $^ -c
