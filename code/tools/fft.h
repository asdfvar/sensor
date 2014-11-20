#ifndef _FFT_H_
#define _FFT_H_

#ifdef __cplusplus
extern "C" {
#endif

int fft(float *x, int N);
int ifft(float *x, int N);

#ifdef __cplusplus
}
#endif

#endif
