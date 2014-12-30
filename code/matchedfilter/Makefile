CPPC = g++
CL = ar rcs

LIBEXE = libmatflt.a

TOOLS = ../tools

INC = -I$(TOOLS)

OBJ = mf_main.o matchedfilter.o run.o crosscorr.o

all: $(OBJ)
	$(CL) $(LIBEXE) $(OBJ)

mf_main.o: mf_main.cpp
	$(CPPC) $^ -c $(INC)

clean:
	rm $(OBJ) $(LIBEXE)

matchedfilter.o: matchedfilter.cpp
	$(CPPC) $^ -c

run.o: run.cpp
	$(CPPC) $^ -c $(INC)

crosscorr.o: crosscorr.cpp
	$(CPPC) $^ -c $(INC)
