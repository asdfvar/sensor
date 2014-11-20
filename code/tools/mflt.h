/*
 * Matched filter functions
 *
 */

namespace mflt {

   void FFT(float *data, int N);
   void iFFT(float *data, int N);

   void crosscorr (
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

         int    *shift); /* the circular shift the reference signal
                        must do to best align with the signal */

   float energy_spectral_density(
         float *data,
         int N,
         float dd);

}
