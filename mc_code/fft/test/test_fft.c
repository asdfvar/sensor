#include "fft.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gettime.h"

#define N 512

int main()
{

   float *x  = (float*)malloc( (N+2) * sizeof(*x));
   float *y  = (float*)malloc( (N+2) * sizeof(*y));
   float *y2 = (float*)malloc( (N+2) * sizeof(*y2));
   float *z  = (float*)malloc( (N+2) * sizeof(*z));
   float *w  = (float*)malloc( (N+2) * sizeof(*w));
   float *workspace = (float*)malloc( 2048 * sizeof(float));

   float dt;

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

   gettime();
   dft_r2c(x, y, w, N);
   dt = gettime();
   printf("DFT time = %.16f\n", dt);

   gettime();
   fft_front_r2c(x, y2, N, workspace);
   dt = gettime();
   printf("Local FFT time = %.16f\n", dt);

   for (k = 0; k < N; k++) z[k] = x[k];

#if 0
   gettime();
   fft(z, N);
   dt = gettime();
   printf("FFTW time = %.16f\n", dt);
#endif

   printf("FFTW      | DFT       | local FFT:\n");
   for (k = 0; k <= N; k++) printf("%f, %f, %f\n", z[k], y[k], y2[k]);
   printf("\n");

   return 0;
}
