extern "C" {
#include "fft.h"
}
#include "matchedfilter.h"
#include <cmath>

void matchedfilter::crosscorr( float *ref, float *sig, int N, float *corr, int *shift)
{

   float tmp;

   /* Compute the norm squared of the reference
      signal and the signal */
   float norm_ref2 = 0.0,
         norm_sig2 = 0.0;
   for (int k = 0; k < N; k++){
      norm_ref2 += ref[k]*ref[k];
      norm_sig2 += sig[k]*sig[k];
   }

   // FFT both signals
   fft(ref, N);
   fft(sig, N);

   /* Conjugate multiply the reference (conjugate)
      to the signal */
   for (int k = 0; k < N+2; k+=2) {
      tmp = ref[k]*sig[k] + ref[k+1]*sig[k+1];
      sig[k+1] = ref[k]*sig[k+1] - ref[k+1]*sig[k];
      sig[k] = tmp;
   }

   ifft(sig, N);

   float max = sig[0];
   int max_ind = 0;

   for (int k = 1; k < N; k++) {
      if (sig[k] > max){
         max = sig[k];
         max_ind = k;
      }
   }

   *shift = max_ind;
   *corr = max / sqrtf(norm_ref2 * norm_sig2);

}
