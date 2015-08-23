#ifndef MATCH_FILT_TRAINING_H
#define MATCH_FILT_TRAINING_H

#include "fileio.h"

void match_filt_training(
              matchedfilter *MF,
              fio::kinIO *KIN,
              float *taper,
              fio::parameters*);

#endif
