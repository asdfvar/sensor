#ifndef PHASE_CORRELATION_H
#define PHASE_CORRELATION_H

namespace phase
{
 void phase_correlation(
             float *ref,
             float *sig,
             float *cross_correlation,
             float norm_ref_in,
             float *norm_sig2,
             float dt,
             float samp_freq,
             int   N_window_ref,
             int   N_data);

 void norm_squared (
             float *signal,
             float *norm,
             int   N_window,
             int   N_data);
}

#endif
