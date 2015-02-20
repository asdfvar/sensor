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
            float *taper,
            bool  apply_taper,
            float *norm_sig2, /* buffer space */
            float dt,
            float samp_freq,
            int N_window_ref,
            int N_data,
            data_form ref_form)
{

   float tmp;
   int k;
   float local_ref_norm;

   if (apply_taper) {
      // FFT the signals
      fft(sig, N_data);

      /* Apply the taper to remove higher frequencies */
      for (k = 0; k < N_data+2; k++) sig[k] *= taper[k];

      ifft(sig, N_data);
   }

   /* Compute the norm squared of the reference
      and the signal */
   norm_sig2[0] = 0.0;
   for (k = 0; k < N_window_ref; k++){
      norm_sig2[0] += sig[k]*sig[k];
   }

   /* Fill the buffer with the normalizing factors of the signal */
   for (k = 1; k < N_data - N_window_ref + 1; k++) {
      norm_sig2[k] = norm_sig2[k-1]     -
                    sig[k-1] * sig[k-1] +
                    sig[k+N_window_ref-1] * sig[k+N_window_ref-1];
   }

   // FFT both signals
   if(ref_form == TIME) fft(ref, N_data);
   fft(sig, N_data);

   if (apply_taper) {

      for (k = 0; k < N_data+2; k++) ref[k] *= taper[k];

      local_ref_norm = 0.0f;

      // Use Parceval's theorem from DC to nyquist (+)
      for (k = 0; k < N_data + 2; k++) local_ref_norm += ref[k]*ref[k];
      // Use Parceval's theorem on the negative frequencies (-)
      for (k = 2; k < N_data; k++) local_ref_norm += ref[k]*ref[k];

      local_ref_norm /= (float)N_data;
      local_ref_norm = sqrtf(local_ref_norm);

   } else {
      local_ref_norm = norm_ref_in;
   }

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
      sig[k] /= sqrtf( norm_sig2[k] ) * local_ref_norm;

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

   int   shift = max_ind; // The number of cells the reference must shift to best match the signal
   float corr  = max;     // The normalized correlation after matching the reference to the signal

   /* Bring the reference signal back to temporal units */
   if(ref_form == TIME) ifft(ref, N_data);

   return corr;

}
