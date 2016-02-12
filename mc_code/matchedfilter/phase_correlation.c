/* This routine computes the cross correlation between the reference and the
 * signal.
 *
 * On input, the reference and signal and in the time domain. On output,
 * The signal is the cross correlation between the reference and the signal.
 */

#include "fft.h"
#include "phase_correlation.h"
#include "local_trig.h"
#include <stdio.h>

/*
 * Function NAME: norm_squared
 */
 void norm_squared_f (
             float *__restrict__ signal,
             float *__restrict__ norm,
             int   N_window,
             int   N_data)
 {
    int k;
    int N_data_reference = N_data - N_window;

    for (k = 0; k < N_data; k++)
    {
       norm[k] = signal[k] * signal[k];
    }
 
    float tmp = 0.0f;
    for (k = 0; k < N_window; k++)
    {
       tmp += norm[k];
    }
 
    float tmp2;
    for (k = 0; k < N_data_reference; k++)
    {
       tmp2     = norm[k];
       norm[k]  = tmp;
       tmp     += norm[ k + N_window ] - tmp2;
    }
    norm[N_data_reference] = tmp;
 
 }
 
/*
 * Function NAME: phase_correlation
 */
 void phase_correlation(
             float *__restrict__ ref,
             float *__restrict__ signal,
             float *__restrict__ cross_correlation,
             float *__restrict__ workspace,
             int   N_data)
 {
 
    float tmp;
    int k;

    float *buffer = workspace; workspace += N_data;

    for (k = 0; k < N_data; k++) buffer[k] = ref[k];

    local_fft_wrapper_r2c(buffer,
                          ref,
                          N_data,
                          workspace);
 
    local_fft_wrapper_r2c(signal,
                          buffer,
                          N_data,
                          workspace);

    /* Conjugate multiply the reference (conjugate) */
 
    for (k = 0; k < N_data+2; k+=2) {
       tmp = ref[k]*buffer[k] + ref[k+1]*buffer[k+1];
       buffer[k+1] = ref[k]*buffer[k+1] - ref[k+1]*buffer[k];
       buffer[k] = tmp;
    }
 
    local_ifft_wrapper_c2r(buffer,
                           cross_correlation,
                           N_data,
                           workspace);

    return;
 }
