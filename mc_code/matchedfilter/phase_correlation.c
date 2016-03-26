/* This routine computes the cross correlation between the reference and the
** signal.
**
** On input, the reference and signal and in the time domain. On output,
** The signal is the cross correlation between the reference and the signal.
*/

#include "fft.h"
#include "phase_correlation.h"
#include "local_trig.h"
#include <stdio.h>

/*
** Function NAME: norm_squared
**
** Computes an array of the square of the normalizing factor
** over a specefied length.
**
** norm_i^2 = sum(signal_j*2, j = i to i + N_window - 1)
*/
 void norm_squared_f (
  /*[I ]*/   float *__restrict__ signal,
  /*[I ]*/   float *__restrict__ norm,
  /*[I ]*/   int                 N_window,
  /*[I ]*/   int                 N_data)
 {
    int k;
    int N_data_reference = N_data - N_window;

    /*
    ** Start by setting norm = signal^2
    */
    for (k = 0; k < N_data; k++)
    {
       norm[k] = signal[k] * signal[k];
    }
 
    float tmp = 0.0f;
    for (k = 0; k < N_window; k++)
    {
       tmp += norm[k];
    }
 
    /*
    ** Populate the norm array with the final result by using a technique
    ** of subtracting off the first element and adding on the last element
    ** at the appropriate places.
    */
    float tmp2;
    for (k = 0; k < N_data_reference; k++)
    {
       tmp2     = norm[k];
       norm[k]  = tmp;
       tmp     += norm[ k + N_window ] - tmp2;
    }
    norm[N_data_reference] = tmp;
 
    return;
 }
 
/*
** Function NAME: freq_norm_squared
**
**    Computes the normalizing factor of the reference data.
**    The reference data is in frequency space so this makes
**    use of Parceval's theorem.
**
*/
 float freq_norm_squared_f (
  /*[I ]*/   float *__restrict__ reference, /* reference data in frequency space */
  /*[I ]*/   int                 N_data)
 {

    int k;
    float norm = 0.0f;

    for (k = 0; k < N_data; k++) norm += 2.0f * reference[k] * reference[k];

    // nyquist
    norm += reference[N_data] * reference[N_data];

    norm /= (float)N_data;

    return norm;
 }
/*
 * Function NAME: phase_correlation
 */
 void phase_correlation(
  /*[I*]*/       float *__restrict__ ref,
  /*[I ]*/       float *__restrict__ signal,
  /*[ O]*/       float *__restrict__ cross_correlation,
  /*[**]*/       float *__restrict__ workspace,
  /*[I ]*/       int                 N_data)
 {
 
    float tmp;
    int k;

    float *buffer = workspace; workspace += N_data;

    local_fft_wrapper_r2c(signal,
                          buffer,
                          N_data,
                          workspace);

    /*
    ** Conjugate multiply the reference (conjugate)
    */
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
