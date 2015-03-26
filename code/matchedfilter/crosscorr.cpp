/* This routine computes the cross correlation between the reference and the
 * signal.
 *
 * On input, the reference and signal and in the time domain. On output,
 * The signal is the cross correlation between the reference and the signal.
 */

extern "C" {
#include "fft.h"
}
#include "matchedfilter.h"
#include <cmath>
#include <iostream>

float crosscorr(
            float *ref,
            float *sig,
            float norm_ref_in,
            float *norm_sig2, /* buffer space */
            float dt,
            float samp_freq,
            int   N_window_ref,
            int   N_data)
{

   float tmp, tmp2;
   int k;

   /* Compute the norm squared of the signal */
   for (k = 0; k < N_data; k++){
      norm_sig2[k] = sig[k] * sig[k];
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

   // FFT
   fft(sig, N_data);

   /* Conjugate multiply the reference (conjugate)
      to the signal and overwrite the signal */
   for (k = 0; k < N_data+2; k+=2) {
      tmp = ref[k]*sig[k] + ref[k+1]*sig[k+1];
      sig[k+1] = ref[k]*sig[k+1] - ref[k+1]*sig[k];
      sig[k] = tmp;
   }

   /* At this point, sig represents the cross correlation squared between
    * the reference and the signal */

   ifft(sig, N_data);

   /* lower bound the correlation by zero prior to squaring it */
   for (k = 0; k < N_data; k++) sig[k] = (sig[k] > 0.0f) ? sig[k] : 0.0f;

   /* Normalize the correlation and square its magnitude */

   for (k = 0; k < N_data - N_window_ref + 1; k++)
      sig[k] *= sig[k];

   norm_ref_in *= norm_ref_in;

   /* using the square of the correlation allows us to minimize the cost
      of invoking the square root repeatedly*/

   /* We don't care about circular shifts */
   int N_data_ref = N_data - N_window_ref + 1;

   for (k = 0; k < N_data_ref; k++) norm_sig2[k] *= norm_ref_in;

   for (k = 0; k < N_data_ref; k++) sig[k] /= norm_sig2[k];

   float max     = sig[0];
   int   max_ind = 0;

   for (k = 1; k < N_data_ref; k++) {
      if (sig[k] > max){
         max = sig[k];
         max_ind = k;
      }
   }

   max = sqrtf(max);

   int   shift = max_ind; // The number of cells the reference must shift to best match the signal
   float corr  = max;     // The normalized correlation after matching the reference to the signal

   return corr;

}
