/*
 Return the fft (or ifft) of the input x in-place

 fft:
 x is real on input. On output, x is complex stored
 with its first half of its complex symetric part only.

 ifft:
 on input, x is complex stored with the first half of its
 complex symmetric form. On output, x is real.

 The packing format for x is:

        [r_0, 0, ..., r_{N-1}, i_{N-1}, r_{Nyq}]

 the version of the fft API is fftw 3.3.4

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
