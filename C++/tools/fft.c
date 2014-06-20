/*
 It's simple, return the fft (or ifft) of the input x.
 Packing format is important to note.
 The fft handle needs to be delt with.
 destroy_fft when it is no longer needed.

 the fftw 3.3.4 API is used here

 for real to complex fft, the output storage is:

 the full fft data comes out to be complex symmetric which looks like

 [DC, data, Nyquist, conj(data reversed)]

 */

#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>

inline int rfft(float *x, int N) {

  fftwf_plan rplan;
  fftwf_complex *y;

  y = (fftwf_complex*) x;

  rplan = fftwf_plan_dft_r2c_1d(N, x, y, FFTW_ESTIMATE);

  fftwf_execute(rplan);
  fftwf_destroy_plan(rplan);

  return 0;
}
