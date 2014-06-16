/*
 It's simple, return the fft (or ifft) of the input x.
 Packing format is important to note.
 The fft handle needs to be delt with.
 destroy_fft when it is no longer needed.

 the fftw 3.3.4 API is used here

 for real to complex fft, the output storage is:

 r_0, r_1, r_2, ... r_N/2, r_nyq, i_1, i_2, ..., i_N/2

 the full fft data comes out to be complex symmetric which looks like

 [DC, data, Nyquist, conj(data reversed)]

 */

#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>

static int allocs(int N);
static fftwf_complex *y;

inline int rfft(float *x, int N) {

  static int Nrec = 0;
  fftwf_plan rplan;
  int i,j;

  if (N > Nrec) {
    Nrec = N;
    allocs(Nrec);
  }

  rplan = fftwf_plan_dft_r2c_1d(N, x, y, FFTW_ESTIMATE);

  fftwf_execute(rplan);
  fftwf_destroy_plan(rplan);

  // real part
  for (i = 0; i < N/2+1; i++)
    x[i] = y[i][0];

  // imaginary part
  for (i = N/2+1, j = 1; i < N; i++, j++)
    x[i] = y[j][1];

  return 0;
}

/* allocate */

int allocs(int N) {

  static int initial = 0;

  if (initial) {
    initial = 1;
    fftwf_free(y);
  }

  y = (fftwf_complex*) fftwf_malloc (sizeof(y) * N);

  return 0;
}

/* destroy */

int destroy_fft() {

  fftwf_free(y);

  return 0;
}
