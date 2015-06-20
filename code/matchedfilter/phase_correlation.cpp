/* This routine computes the cross correlation between the reference and the
 * signal.
 *
 * On input, the reference and signal and in the time domain. On output,
 * The signal is the cross correlation between the reference and the signal.
 */

extern "C" {
#include "fft.h"
}
#include "phase_correlation.h"
#include <cmath>
#include <iostream>

namespace phase
{
 void norm_squared (
             float *__restrict__ signal,
             float *__restrict__ norm,
             int   N_window,
             int   N_data)
 {
    int N_data_reference = N_data - N_window;
 
    for (int k = 0; k < N_data; k++)
    {
       norm[k] = signal[k] * signal[k];
    }
 
    float tmp = 0.0f;
    for (int k = 0; k < N_window; k++)
    {
       tmp += norm[k];
    }
 
    float tmp2;
    for (int k = 0; k < N_data_reference; k++)
    {
       tmp2     = norm[k];
       norm[k]  = tmp;
       tmp     += norm[ k + N_window ] - tmp2;
    }
    norm[N_data_reference] = tmp;
 
 }
 
 void phase_correlation(
             float *__restrict__ ref,
             float *__restrict__ signal,
             float *__restrict__ cross_correlation,
             float norm_ref_in,
             float *__restrict__ norm_sig2, /* buffer space */
             float dt,
             float samp_freq,
             int   N_window_ref,
             int   N_data)
 {
 
    float tmp;
    int k;
 
 #if 0
    /* Compute the norm squared of the signal */
    for (k = 0; k < N_data; k++){
       norm_sig2[k] = signal[k] * signal[k];
    }
 
    tmp = 0.0f;
    for (k = 0; k < N_window_ref; k++){
       tmp += norm_sig2[k];
    }
 
    for (k = 0; k < N_data - N_window_ref; k++) {
       tmp2          = norm_sig2[k];
       norm_sig2[k]  = tmp;
       tmp          += norm_sig2[k+N_window_ref] - tmp2;
    }
    norm_sig2[k] = tmp;
 #endif
 
    // FFT
    fft(signal, N_data);
 
    /* Conjugate multiply the reference (conjugate)
       to the signal and overwrite the signal */
 
    for (k = 0; k < N_data+2; k+=2) {
       tmp = ref[k]*signal[k] + ref[k+1]*signal[k+1];
       cross_correlation[k+1] = ref[k]*signal[k+1] - ref[k+1]*signal[k];
       cross_correlation[k] = tmp;
    }
 
    ifft(cross_correlation, N_data);
 
 #if 0
    /* Normalize the correlation and square its magnitude */
 
    for (k = 0; k < N_data - N_window_ref + 1; k++)
       signal[k] *= signal[k];
 
    norm_ref_in *= norm_ref_in;
 
    /* using the square of the correlation allows us to minimize the cost
       of invoking the square root repeatedly*/
 
    /* We don't care about circular shifts */
    int N_data_ref = N_data - N_window_ref + 1;
 
    for (k = 0; k < N_data_ref; k++) norm_sig2[k] *= norm_ref_in;
 
    for (k = 0; k < N_data_ref; k++) signal[k] /= norm_sig2[k];
 
    float max     = signal[0];
    int   max_ind = 0;
 
    for (k = 1; k < N_data_ref; k++) {
       if (signal[k] > max){
          max = signal[k];
          max_ind = k;
       }
    }
 
    max = sqrtf(max);
 
    int   shift = max_ind; // The number of cells the reference must shift to best match the signal
    float corr  = max;     // The normalized correlation after matching the reference to the signal
 #endif
 
    return;
 }

}
