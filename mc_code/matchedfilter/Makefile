CPPC = g++
CL = ar rcs
FLAGS = -O3 -Wall

LIBEXE = libmatflt.a

UTILITIES = ../utilities
PREPROC = ../preprocessing

INC = -I$(UTILITIES) -I$(PREPROC)

OBJ = matchedfilter.o phase_correlation.o match_filt_training.o run_mf.o

## BUILD ALL

all: $(OBJ)
	$(CL) $(LIBEXE) $(OBJ)

## CLEAN ALL

clean:
	rm $(OBJ) $(LIBEXE)

## Create Objects

matchedfilter.o: matchedfilter.c
	$(CPPC) $^ -c -std=c++0x $(INC) $(FLAGS)

run_mf.o: run_mf.c
	$(CPPC) $^ -c $(INC) $(FLAGS)

phase_correlation.o: phase_correlation.c
	$(CPPC) $^ -c $(INC) $(FLAGS)

match_filt_training.o: match_filt_training.c
	$(CPPC) $^ -c $(INC) $(FLAGS)
