#include "fft.h"
#include <stdio.h>
#include <stdlib.h>

#define N 20

int main()
{

   float *x = (float*)malloc( (N+2) * sizeof(*x));
   float *y = (float*)malloc( (N+2) * sizeof(*x));
   float *z = (float*)malloc( (N+2) * sizeof(*x));
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

   printf("produce DFT outputs of:\n");

   dft_r2c(x, y, N, workspace);

   for (k = 0; k < N; k++)
   {
      printf("%f, ", y[k]);
   }
   printf("\n");

   printf("FFTW outputs:\n");

   for (k = 0; k < N; k++) z[k] = x[k];
   fft(z, N);

   for (k = 0; k < N; k++)
   {
      printf("%f, ", z[k]);
   }
   printf("\n");

   return 0;
}
