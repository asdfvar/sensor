/*
 program to test the fft

 when installing fftw on *nix systems, be sure to enable floating point accuracy via
 ./configure --enable-float
 */

extern "C" {
#include "fft.h"
}
#include <iostream>
#include <stdio.h>


int main() {

  int N = 8;
  float *x = new float [N+1];

  std::cout << "about to perform the FFT:" << std::endl;

  // uniformly distributed random data:

  x[0] = 0.31505814;
  x[1] = 0.51839913;
  x[2] = 0.12792421;
  x[3] = 0.70006998;
  x[4] = 0.23771298;
  x[5] = 0.82811662;
  x[6] = 0.81617928;
  x[7] = 0.99628785;

 /* the fft output results in full form are:

     fft(x) = 4.5397829
              0.06779949 + 1.11671607i
             -0.39133236 + 0.34984209i
              0.08689083 - 0.25979406i
             -1.54599897
              0.08689083 + 0.25979406i
             -0.39133236 - 0.34984209i
              0.06779949 - 1.11671607i

    but the actual output is only half packed
 */

  fft(x,N);

  // print fft results (packed)

  for (int i = 0; i < N+1; i++)
    printf("%f\n", x[i]);
  std::cout << std::endl;

  std::cout << "about to perform the inverse FFT:" << std::endl;

  ifft(x,N);

  for (int i = 0; i < N; i++)
    printf("%f\n", x[i]);

  // free the memory

  delete x;

  return 0;
}
