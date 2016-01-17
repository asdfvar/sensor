#include "fft.h"
#include <fftw3.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "gettime.h"

#define N_size 16

int main()
{

   float *buffer = (float*)malloc( 5*(N_size+2)*32768 * sizeof(float));
   float *workspace = buffer;

   float *x  = workspace; workspace += N_size+2;
   float *y  = workspace; workspace += N_size+2;
   float *z  = workspace; workspace += N_size+2;
   float *y2 = workspace; workspace += N_size+2;
   float *w  = workspace; workspace += N_size+2;

   float dt_dft, dt_fftw, dt_fftl;

   srand(0);

   int k;
   int samples = 1;
   printf("Inputs of\nx = ");
   for (k = 0; k < N_size; k++)
   {
      x[k] = (float)rand() / (float)RAND_MAX;
      printf("%f, ", x[k]);
   }
   printf("\n");

   /*
   ** Compute the twiddle factors
   */
   const float neg_two_pi_N_inv = - TWO_PI / (float)N_size;
   for (k = 0; k <= N_size; k++)
   {
      w[2*k  ] = cosf( neg_two_pi_N_inv * k );
      w[2*k+1] = sinf( neg_two_pi_N_inv * k );
   }

   gettime();
   for (k = 0; k < samples; k++) {
      dft_r2c(x, y, w, N_size);
   }
   dt_dft = gettime();

   gettime();
   for (k = 0; k < samples; k++) {
      local_fft_wrapper_r2c(x, y2, N_size, LOC_FFT_FWD, workspace);
   }
   dt_fftw = gettime();

   for (k = 0; k < N_size; k++) z[k] = x[k];

   gettime();
   for (k = 0; k < samples/2; k++) {
      fft(z, N_size);
      ifft(z, N_size);
   }
   dt_fftl = gettime();
   fft(z, N_size);

   printf("FFTW      | DFT       | local FFT:\n");
   for (k = 0; k <= N_size+1; k++) printf("%f, %f, %f\n", z[k], y[k], y2[k]);
   printf("\n");

   printf("DFT time       = %.16f : ave: %.16f\n", dt_dft, dt_dft / (float) samples);
   printf("Local FFT time = %.16f : ave: %.16f\n", dt_fftw, dt_fftw / (float) samples);
   printf("FFTW time      = %.16f : ave: %.16f\n", dt_fftl, dt_fftl / (float) samples);

   for (k = 0; k < N_size; k++) x[k] = (float)rand() / (float)RAND_MAX;
   for (k = 0; k < N_size; k++) z[k] = x[k];

   local_fft_wrapper_r2c(z, y, N_size, LOC_FFT_FWD, workspace);

   /*
   ** Compute the twiddle factors
   */
   const float two_pi_N_inv = TWO_PI / (float)N_size;
   for (k = 0; k <= N_size; k++)
   {
      w[2*k  ] = cosf( two_pi_N_inv * k );
      w[2*k+1] = sinf( two_pi_N_inv * k );
   }
#if 0
   idft_c2r(y, z, w, N_size);
   for (k = 0; k < N_size; k++) z[k] /= (float)N_size;
#else
   local_ifft_wrapper_c2r(y,
                          z,
                          N_size,
                          workspace);
#endif

   printf("x  |   idft(fft(x)):\n");
   for (k = 0; k < N_size; k++) printf("%f, %f\n", x[k], z[k]);
   printf("\n");

   free(buffer);

   return 0;
}
