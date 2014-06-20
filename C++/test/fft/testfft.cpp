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

  std::cout << "about to perform the fft" << std::endl;

  float *x = new float [9];

  // uniform random input example:

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

  rfft(x,8);

  // print fft results as they are packed

  for (int i = 0; i < 9; i++)
    printf("%f\n", x[i]);

  // free the memory

  delete x;
#if 0
  destroy_fft();
#endif

  return 0;
}
