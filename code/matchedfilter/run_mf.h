#ifndef RUN_MF_H
#define RUN_MF_H

void run_mf (matchedfilter *MF,
             float         *ax,
             float         *ay,
             float          dt,
             float          samp_freq,
             int            N_data,
             float         *buf);

#endif
