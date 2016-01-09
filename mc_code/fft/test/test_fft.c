#include "fft.h"
#include <fftw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gettime.h"

#define N 400

int main()
{

   float *buffer = (float*)malloc( 5*(N+2)*32768 * sizeof(float));
   float *workspace = buffer;

   float *z  = workspace; workspace += N+2;
   float *x  = workspace; workspace += N+2;
   float *y  = workspace; workspace += N+2;
   float *y2 = workspace; workspace += N+2;
   float *w  = workspace; workspace += N+2;

   float dt_dft, dt_fftw, dt_fftl;

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
   dt_dft = gettime();

   gettime();
   fft_front_r2c(x, y2, N, workspace);
   dt_fftw = gettime();

   for (k = 0; k < N; k++) z[k] = x[k];

   gettime();
   fft(z, N);
   dt_fftl = gettime();

   printf("FFTW      | DFT       | local FFT:\n");
   for (k = 0; k <= N; k++) printf("%f, %f, %f\n", z[k], y[k], y2[k]);
   printf("\n");

   printf("DFT time = %.16f\n", dt_dft);
   printf("Local FFT time = %.16f\n", dt_fftw);
   printf("FFTW time = %.16f\n", dt_fftl);
   free(buffer);

   return 0;
}
