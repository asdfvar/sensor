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

void matchedfilter::crosscorr(float *ref,
                              float *sig,
                              float *norm_sig2, /* buffer space */
                              float dt, float samp_freq,
                              int N_window_ref, int N_data,
                              float *corr, int *shift, data_form ref_form)
{

   float tmp;
   int k;

   /* Compute the norm squared of the reference
      signal and the signal */
   float norm_ref2 = 0.0;
   norm_sig2[0] = 0.0;
   for (k = 0; k < N_window_ref; k++){
      norm_ref2    += ref[k]*ref[k];
      norm_sig2[0] += sig[k]*sig[k];
   }

   /* Fill the buffer with the normalizing factors of the signal */
   for (k = 1; k < N_data - N_window_ref + 1; k++) {
      norm_sig2[k] = norm_sig2[k-1]     -
                    sig[k-1] * sig[k-1] +
                    sig[k+N_window_ref-1] * sig[k+N_window_ref-1];
   }

   // FFT both signals
   fft(ref, N_data);
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

   /* Normalize the correlation */

   for (k = 0; k < N_data - N_window_ref + 1; k++)
      sig[k] /= sqrtf( norm_sig2[k] * norm_ref2 );

   /* We don't care about circular shifts */
   for (k = N_data - N_window_ref + 1; k < N_data; k++)
      sig[k] = 0.0;

   float max = sig[0];
   int max_ind = 0;

   for (k = 1; k < N_data - N_window_ref + 1; k++) {
      if (sig[k] > max){
         max = sig[k];
         max_ind = k;
      }
   }

   *shift = max_ind;
   *corr = max;

   /* Bring the reference signal back to temporal units */
   ifft(ref, N_data);

}
