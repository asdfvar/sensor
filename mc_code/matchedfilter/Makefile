CC = gcc
CL = ar rcs
FLAGS = -O3 -Wall

LIBEXE = libmatflt.a

UTILITIES = ../utilities
PREPROC = ../preprocessing

INC = -I$(UTILITIES) -I$(PREPROC)

OBJ = phase_correlation.o run_mf.o

## BUILD ALL

all: $(OBJ)
	$(CL) $(LIBEXE) $(OBJ)

## CLEAN ALL

clean:
	rm $(OBJ) $(LIBEXE)

## Create Objects

matchedfilter.o: matchedfilter.c
	$(CC) $^ -c $(INC) $(FLAGS)

run_mf.o: run_mf.c
	$(CC) $^ -c $(INC) $(FLAGS)

phase_correlation.o: phase_correlation.c
	$(CC) $^ -c $(INC) $(FLAGS)

match_filt_training.o: match_filt_training.c
	$(CC) $^ -c $(INC) $(FLAGS)
