BASE = .
CC   = gcc
OBJ  = sensor_main.o example.o
LIBS = -lpreproc -lmatflt -lutils -ltest -lfft -lfftw3f -lm

MATCHEDFILTER = matchedfilter/
UTILITIES = utilities/
PREPROCESSING = preprocessing/
UNITTEST = unit_test/
FFT = fft/

INC  = -I$(BASE)/$(PREPROCESSING) -I$(BASE)/$(MATCHEDFILTER) \
       -I$(BASE)/$(UTILITIES) -I$(BASE)/$(UNITTEST) -I$(BASE)/$(FFT)
LIBPATHS = -L$(BASE)/$(PREPROCESSING) -L$(BASE)/$(MATCHEDFILTER) \
           -L$(BASE)/$(UTILITIES) -L$(BASE)/$(UNITTEST) -L$(BASE)/$(FFT)

EXE = example

all: $(OBJ)
	cd $(MATCHEDFILTER) && $(MAKE)
	cd $(UTILITIES) && $(MAKE)
	cd $(PREPROCESSING) && $(MAKE)
	cd $(UNITTEST) && $(MAKE)
	cd $(FFT) && $(MAKE)
	$(CC) $(OBJ) -o $(EXE) $(INC) $(LIBPATHS) $(LIBS)

clean:
	rm $(OBJ) $(EXE)
	make -C $(MATCHEDFILTER) clean
	make -C $(UTILITIES) clean
	make -C $(PREPROCESSING) clean
	make -C $(UNITTEST) clean
	make -C $(FFT) clean

sensor_main.o: sensor_main.c
	$(CC) $^ -c $(INC)

example.o: example.c
	$(CC) $^ -c $(INC)
