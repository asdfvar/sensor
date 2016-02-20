#include "local_trig.h"
#include "fft.h"
#include <math.h>

inline void local_fft_wrapper_r2c(float *x,
                                  float *y,
                                  int    N,
                                  float *workspace)
{

   int k;
   const float two_pi_N_inv = TWO_PI / (float)N;

   float *w = workspace;
   workspace += 2*N;

   /*
   ** Compute the twiddle factors
   */
   for (k = 0; k <= N; k++)
   {
      w[2*k  ] = cosf( -two_pi_N_inv * (float)k );
      w[2*k+1] = sinf( -two_pi_N_inv * (float)k );
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
                 0,
                 0,
                 workspace);

   if ( N % 2 == 0) y[N] = nyquist;

}
