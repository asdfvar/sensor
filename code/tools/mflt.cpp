extern "C" {
#include "fft.h"
}
#include <cmath>
#include <iostream>

namespace mflt {

   void FFT(float *data, int N) {
//      fft(data, N);
std::cout << "do the fft" << std::endl;
   }

/************************************************************************/

   void iFFT(float *data, int N) {
//      ifft(data, N);
std::cout << "do the ifft" << std::endl;
   }

/************************************************************************/

   void crosscorr(
      /* Computes the cross correlation between the reference
         signal and the signal. */
         float *ref, /* Reference signal.

                        ref must have at least N+2 elements of
                        space allocated to it.
                        
                        On input, ref is in time. On output, ref
                        is in frequency.*/

         float *sig, /* Signal.

                        sig must have at least N+2 elements of
                        space allocated to it.

                        On input, sig is in time. On output, sig
                        is the cross correlation of ref and sig.*/

         int    N,   /* Number of elements in both the reference
                        signal and the signal. */

         float *correlation, /* The best correlation between
                        the signals */

         int    *shift) /* the circular shift the reference signal
                        must do to best align with the signal */
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
      FFT(ref, N);
      FFT(sig, N);

      /* Conjugate multiply the reference (conjugate)
         to the signal */
      for (int k = 0; k < N+2; k+=2) {
         tmp = ref[k]*sig[k] + ref[k+1]*sig[k+1];
         sig[k+1] = ref[k]*sig[k+1] - ref[k+1]*sig[k];
         sig[k] = tmp;
      }

      iFFT(sig, N);

      float max = sig[0];
      int max_ind = 0;

      for (int k = 1; k < N; k++) {
         if (sig[k] > max){
            max = sig[k];
            max_ind = k;
         }
      }

      *shift = max_ind;
      *correlation = max / sqrtf(norm_ref2 * norm_sig2);

   }

/************************************************************************/

   float energy_spectral_density (
      float *data,
      int N,
      float dd) /* If data is temporal, this is dt
                   if data is frequency, this is df */
   {

      float Energy = 0.0;
      for ( int i = 0; i < N; i++ ) {
         Energy += data[i]*data[i];
      }

      Energy *= dd;
      return Energy;

   }
}
