#include <math.h>
#include "fft.h"

void fft_front_r2c(float *x,
                   float *y,
                   int    N,
                   float *workspace)
{

   int k;
   const float neg_two_pi_N_inv = - TWO_PI / (float)N;

   float *w = workspace;
   workspace += N;

   /*
   ** Compute the twiddle factors
   */
   for (k = 0; k <= N; k++)
   {
      w[2*k  ] = cosf( neg_two_pi_N_inv * k );
      w[2*k+1] = sinf( neg_two_pi_N_inv * k );
   }

   fft_l_r2c(x,
             y,
             w,
             N,
             workspace);

}
