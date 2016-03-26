#ifndef PHASE_CORRELATION_H
#define PHASE_CORRELATION_H

 void phase_correlation(
             float *ref,
             float *sig,
             float *cross_correlation,
             float *workspace,
             int    N_data);

 void norm_squared_f (
             float *signal,
             float *norm,
             int   N_window,
             int   N_data);

 float freq_norm_squared_f (
             float *reference,
             int    N_data);

#endif
