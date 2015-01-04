CPPC = g++
CL = ar rcs
FLAGS = -O3 -Wall

LIBEXE = libmatflt.a

TOOLS = ../tools
PREPROC = ../preprocessing

INC = -I$(TOOLS) -I$(PREPROC)

OBJ = matchedfilter.o crosscorr.o match_filt_training.o

## BUILD ALL

all: $(OBJ)
	$(CL) $(LIBEXE) $(OBJ)

## CLEAN ALL

clean:
	rm $(OBJ) $(LIBEXE)

## Create Objects

matchedfilter.o: matchedfilter.cpp
	$(CPPC) $^ -c $(INC) $(FLAGS)

crosscorr.o: crosscorr.cpp
	$(CPPC) $^ -c $(INC) $(FLAGS)

match_filt_training.o: match_filt_training.cpp
	$(CPPC) $^ -c $(INC) $(FLAGS)
