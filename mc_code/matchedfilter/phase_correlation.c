/* This routine computes the cross correlation between the reference and the
 * signal.
 *
 * On input, the reference and signal and in the time domain. On output,
 * The signal is the cross correlation between the reference and the signal.
 */

#include "fft.h"
#include "phase_correlation.h"
#include <math.h>

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
             int   N_data)
 {
 
    float tmp;
    int k;

    for (k = 0; k < N_data; k++) cross_correlation[k] = signal[k];
 
    fft(cross_correlation, N_data);
    fft(ref, N_data);
 
    /* Conjugate multiply the reference (conjugate) */
 
    for (k = 0; k < N_data+2; k+=2) {
       tmp = ref[k]*cross_correlation[k] + ref[k+1]*cross_correlation[k+1];
       cross_correlation[k+1] = ref[k]*cross_correlation[k+1] - ref[k+1]*cross_correlation[k];
       cross_correlation[k] = tmp;
    }
 
    ifft(cross_correlation, N_data);
 
    return;
 }
