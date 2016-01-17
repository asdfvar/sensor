#ifndef FFT_H
#define FFT_H

#define TWO_PI 6.283185307179586f

enum {LOC_FFT_FWD, LOC_FFT_BACK};

int fft(float *x, int N);
int ifft(float *x, int N);

void dft_r2c(float *x,
             float *y,
             float *w,
             int N);

void idft_c2r(float *x,
              float *y,
              float *w,
              int N);

void idft_c2c(float *x,
              float *y,
              float *w,
              int N);

void local_fft_r2c(float *x,
                   float *y,
                   float *w,
                   int    N,
                   float *workspace);

void local_fft_wrapper_r2c(float *x,
                           float *y,
                           int    N,
                           int    dir,
                           float *workspace);

void local_ifft_c2r(float *x,
                    float *y,
                    float *w,
                    int    N,
                    float *workspace);

void local_ifft_c2c(float *x,
                    float *y,
                    float *w,
                    int    N,
                    float *workspace);

void local_ifft_wrapper_c2r(float *x,
                            float *y,
                            int    N,
                            float *workspace);

void local_ifft_wrapper_c2c(float *x,
                            float *y,
                            int    N,
                            float *workspace);

#endif
