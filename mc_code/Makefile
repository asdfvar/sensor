BASE = .
CC   = gcc
PREP_OBJ = prep_ref.o
SENSOR_OBJ = sensor_main.o sensor_example.o
TRAINING_OBJ = training_main.o training_example.o

LIBS = -lpreproc -lmatflt -lutils -ltest -lm -lfft #-lfftw3f

MATCHEDFILTER = matchedfilter/
UTILITIES = utilities/
PREPROCESSING = preprocessing/
UNITTEST = unit_test/
FFT = fft/

INC  = -I$(BASE) -I$(BASE)/$(PREPROCESSING) -I$(BASE)/$(MATCHEDFILTER) \
       -I$(BASE)/$(UTILITIES) -I$(BASE)/$(UNITTEST) -I$(BASE)/$(FFT)
LIBPATHS = -L$(BASE)/$(PREPROCESSING) -L$(BASE)/$(MATCHEDFILTER) \
           -L$(BASE)/$(UTILITIES) -L$(BASE)/$(UNITTEST) -L$(BASE)/$(FFT)

SENSOR = sensor_example
TRAIN = training_example

all: COMPILE_LIBS SENSOR TRAIN

COMPILE_LIBS:
	cd $(MATCHEDFILTER) && $(MAKE)
	cd $(UTILITIES) && $(MAKE)
	cd $(PREPROCESSING) && $(MAKE)
	cd $(UNITTEST) && $(MAKE)
	cd $(FFT) && $(MAKE)

SENSOR: $(SENSOR_OBJ) $(PREP_OBJ)
	$(CC) $(SENSOR_OBJ) $(PREP_OBJ) -o $(SENSOR) $(INC) $(LIBPATHS) $(LIBS)

TRAIN: $(TRAINING_OBJ) $(PREP_OBJ)
	$(CC) $(TRAINING_OBJ) $(PREP_OBJ) -o $(TRAIN) $(INC) $(LIBPATHS) $(LIBS)

clean:
	make -C $(MATCHEDFILTER) clean
	make -C $(UTILITIES) clean
	make -C $(PREPROCESSING) clean
	make -C $(UNITTEST) clean
	make -C $(FFT) clean
	rm $(OBJ) $(PREP_OBJ) $(SENSOR_OBJ) $(TRAINING_OBJ) $(SENSOR) $(TRAIN)

prep_ref.o: prep_ref.c
	$(CC) $^ -c $(INC)

sensor_main.o: sensor_main.c
	$(CC) $^ -c $(INC)

sensor_example.o: sensor_example.c
	$(CC) $^ -c $(INC)

training_example.o: training_example.c
	$(CC) $^ -c $(INC)

training_main.o: training_main.c
	$(CC) $^ -c $(INC)
