#include "fft.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define N 16

int main()
{

   float *x  = (float*)malloc( (N+2) * sizeof(*x));
   float *y  = (float*)malloc( (N+2) * sizeof(*x));
   float *y2 = (float*)malloc( (N+2) * sizeof(*x));
   float *z  = (float*)malloc( (N+2) * sizeof(*x));
   float *w  = (float*)malloc( (N+2) * sizeof(*x));
   float *workspace = (float*)malloc( 1024 * sizeof(float));

   srand(0);

   int k;
   printf("Inputs of\nx = ");
   for (k = 0; k < N; k++)
   {
      x[k] = (float)rand() / (float)RAND_MAX;
      printf("%f, ", x[k]);
   }
   printf("\n");

   /*
   ** Compute the twiddle factors
   */
   const float neg_two_pi_N_inv = - TWO_PI / (float)N;
   for (k = 0; k <= N; k++)
   {
      w[2*k  ] = cosf( neg_two_pi_N_inv * k );
      w[2*k+1] = sinf( neg_two_pi_N_inv * k );
   }

   dft_r2c(x, y, w, N);

   fft_front_r2c(x, y2, N, workspace);

   for (k = 0; k < N; k++) z[k] = x[k];
   fft(z, N);

   printf("FFTW      | DFT       | local FFT:\n");
   for (k = 0; k <= N; k++) printf("%f, %f, %f\n", z[k], y[k], y2[k]);
   printf("\n");

   return 0;
}
