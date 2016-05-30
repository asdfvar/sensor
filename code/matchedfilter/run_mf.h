#ifndef RUN_MF_H
#define RUN_MF_H

#include "memory_management.h"

void run_mf (matchedfilter *MF,
             float         *ax,
             float         *ay,
             float          dt,
             float          samp_freq,
             int            N_data,
             bool           debug,
             MEMORY         mem_buffer);

#endif
