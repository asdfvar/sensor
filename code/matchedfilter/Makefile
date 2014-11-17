CPPC = g++
CL = ar rcs

LIBEXE = libmatflt.a

TOOLS = ../tools

INC = -I$(TOOLS)

OBJ = matchedfilter.o

all: $(OBJ)
	$(CL) $(LIBEXE) $(OBJ)

matchedfilter.o: matchedfilter.cpp
	$(CPPC) $(FLAGS) $^ -c $(INC)

clean:
	rm $(OBJ) $(LIBEXE)
