#ifndef FFT_H
#define FFT_H

#define TWO_PI 6.283185307179586f

int fft(float *x, int N);
int ifft(float *x, int N);

void dft_r2c(float *x,
             float *y,
             float *w,
             int    w_start,
             int    w_stride,
             int N);

void idft_c2r(float *x,
              float *y,
              float *w,
              int    start,
              int    stride,
              int    N,
              int    N_orig);

void idft_c2c(float *x,
              float *y,
              float *w,
              int    start,
              int    stride,
              int    N_orig,
              int    N);

void local_fft_r2c(float *x,
                   float *y,
                   float *w,
                   int    N,
                   int    stride,
                   int    start,
                   float *workspace);

void local_fft_wrapper_r2c(float *x,
                           float *y,
                           int    N,
                           float *workspace);

void local_ifft_c2r(float *x,
                    float *y,
                    float *w,
                    int    start,
                    int    stride,
                    int    N,
                    int    N_orig,
                    float *workspace);

void local_ifft_c2c(float *x,
                    float *y,
                    float *w,
                    int    start,
                    int    stride,
                    int    N,
                    int    N_orig,
                    float *workspace);

void local_ifft_wrapper_c2r(float *x,
                            float *y,
                            int    N,
                            float *workspace);

float get_element_conj_sym(
                      float *x,       /* The conjugate symmetric array    */
                      int    start,   /* starting location on the array   */
                      int    stride,  /* elements to stride by from start */
                      int    N,       /* number of elements in this array */
                      int    element, /* the select element from start    */
                      int    part);   /* real part = 1, imag part = 2     */

inline float *ref_element(
                      float *x,       /* The  array                       */
                      int    start,   /* starting location on the array   */
                      int    stride,  /* elements to stride by from start */
                      int    element, /* the select element from start    */
                      int    words);   /* number of words per element      */

#endif
