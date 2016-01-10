#include "local_trig.h"
#include "fft.h"

inline void local_fft_wrapper_r2c(float *x,
                                  float *y,
                                  int    N,
                                  int    dir,
                                  float *workspace)
{

   int k;
   const float two_pi_N_inv = TWO_PI / (float)N;

   float *w = workspace;
   workspace += 2*N;

   /*
   ** Compute the twiddle factors
   */
   if (dir == LOC_FFT_FWD)
   {
      for (k = 0; k <= N; k++)
      {
         w[2*k  ] = local_cos( -two_pi_N_inv * (float)k );
         w[2*k+1] = local_sin( -two_pi_N_inv * (float)k );
      }
   }
   else if (dir == LOC_FFT_BACK)
   {
      for (k = 0; k <= N; k++)
      {
         w[2*k  ] = local_cos( -two_pi_N_inv * (float)k );
         w[2*k+1] = local_sin( -two_pi_N_inv * (float)k );
      }
   }

   /*
   ** Compute nyquist
   */
   float nyquist = 0.0f;
   for (k = 0; k < N; k++) nyquist = x[k] - nyquist;
   nyquist = -nyquist;

   local_fft_r2c(x,
                 y,
                 w,
                 N,
                 workspace);

   if (dir == LOC_FFT_BACK)
   {
      const float scale = 1.0f / (float)N;
      for (k = 0; k < N; k++) y[k] *= scale;
   }

   y[N] = nyquist;

}
