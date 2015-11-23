BASE = .
CC   = gcc
OBJ  = sensor_main.o example.o
LIBS = -lpreproc -lmatflt -lutils -lfftw3f -lm

MATCHEDFILTER = matchedfilter/
UTILITIES = utilities/
PREPROCESSING = preprocessing/

INC  = -I$(BASE)/$(PREPROCESSING) -I$(BASE)/$(MATCHEDFILTER) \
       -I$(BASE)/$(UTILITIES)
LIBPATHS = -L$(BASE)/$(PREPROCESSING) -L$(BASE)/$(MATCHEDFILTER) \
           -L$(BASE)/$(UTILITIES)

EXE = example

all: $(OBJ)
	cd $(MATCHEDFILTER) && $(MAKE)
	cd $(UTILITIES) && $(MAKE)
	cd $(PREPROCESSING) && $(MAKE)
	$(CC) $(OBJ) -o $(EXE) $(INC) $(LIBPATHS) $(LIBS)

clean:
	rm $(OBJ) $(EXE)
	make -C $(MATCHEDFILTER) clean
	make -C $(UTILITIES) clean
	make -C $(PREPROCESSING) clean

sensor_main.o: sensor_main.c
	$(CC) $^ -c $(INC)

example.o: example.c
	$(CC) $^ -c $(INC)
