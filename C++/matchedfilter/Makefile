CPPC = g++
CL = ar rcs

LIB = libmatflt.a

OBJ = matchedfilter.o

all: $(OBJ)
	$(CL) $(LIB) $(OBJ)

matchedfilter.o: matchedfilter.cpp
	$(CPPC) $^ -c

clean:
	rm $(OBJ) $(LIB)
