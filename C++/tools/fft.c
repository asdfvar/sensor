/*
 Return the fft (or ifft) of the input x in-place

 x real on input into the fft
   complex on input into the ifft but real on output

 the fftw 3.3.4 API is used here

 */

#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>

/***************
 * forward FFT *
 ***************/

inline int fft(float *x, int N) {

  fftwf_plan rplan;
  fftwf_complex *y;

  y = (fftwf_complex*) x;

  rplan = fftwf_plan_dft_r2c_1d(N, x, y, FFTW_ESTIMATE);

  fftwf_execute(rplan);
  fftwf_destroy_plan(rplan);

  return 0;
}

/***************
 * inverse FFT *
 ***************/

inline int ifft(float *x, int N) {

  fftwf_plan rplan;
  fftwf_complex *y;

  y = (fftwf_complex*) x;

  rplan = fftwf_plan_dft_c2r_1d(N, y, x, FFTW_ESTIMATE);

  fftwf_execute(rplan);
  fftwf_destroy_plan(rplan);

  float divN = 1.0/N;

  int i;
  for (i = 0; i < N; i++)
    x[i] *= divN;

  return 0;
}
