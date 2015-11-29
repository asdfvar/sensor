BASE = .
CC   = gcc
OBJ  = sensor_main.o example.o
LIBS = -lpreproc -lmatflt -lutils -ltest -lfftw3f -lm

MATCHEDFILTER = matchedfilter/
UTILITIES = utilities/
PREPROCESSING = preprocessing/
UNITTEST = unit_test/

INC  = -I$(BASE)/$(PREPROCESSING) -I$(BASE)/$(MATCHEDFILTER) \
       -I$(BASE)/$(UTILITIES) -I$(BASE)/$(UNITTEST)
LIBPATHS = -L$(BASE)/$(PREPROCESSING) -L$(BASE)/$(MATCHEDFILTER) \
           -L$(BASE)/$(UTILITIES) -L$(BASE)/$(UNITTEST)

EXE = example

all: $(OBJ)
	cd $(MATCHEDFILTER) && $(MAKE)
	cd $(UTILITIES) && $(MAKE)
	cd $(PREPROCESSING) && $(MAKE)
	cd $(UNITTEST) && $(MAKE)
	$(CC) $(OBJ) -o $(EXE) $(INC) $(LIBPATHS) $(LIBS)

clean:
	rm $(OBJ) $(EXE)
	make -C $(MATCHEDFILTER) clean
	make -C $(UTILITIES) clean
	make -C $(PREPROCESSING) clean
	make -C $(UNITTEST) clean

sensor_main.o: sensor_main.c
	$(CC) $^ -c $(INC)

example.o: example.c
	$(CC) $^ -c $(INC)
