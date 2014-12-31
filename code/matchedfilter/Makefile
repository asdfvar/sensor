CPPC = g++
CL = ar rcs

LIBEXE = libmatflt.a

TOOLS = ../tools

INC = -I$(TOOLS)

OBJ = matchedfilter.o crosscorr.o

## BUILD ALL

all: $(OBJ)
	$(CL) $(LIBEXE) $(OBJ)

## CLEAN ALL

clean:
	rm $(OBJ) $(LIBEXE)

## Create Objects

matchedfilter.o: matchedfilter.cpp
	$(CPPC) $^ -c

crosscorr.o: crosscorr.cpp
	$(CPPC) $^ -c $(INC)
