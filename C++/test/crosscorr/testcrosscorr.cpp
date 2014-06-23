/* Test the cross correlation */

extern "C" {
#include "fft.h"
}
#include <iostream>
#include <stdio.h>

#define N 10

int main() {

  float ref[N] = {0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  float sig[N] = {0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  float tmp;

  // take the FFT of both signals

  fft(ref, N);
  fft(sig, N);

  // conjugate the reference

  for (int i = 1; i < N; i+=2)
    ref[i] = -ref[i];

  // multiply the refence to the signal (Complex)

  for (int i = 0; i < N; i+=2) {
    tmp = sig[i]*ref[i] - sig[i+1]*ref[i+1];
    sig[i+1] = sig[i]*ref[i+1] + ref[i]*sig[i+1];
    sig[i] = tmp;
  }

  // take the inverse fft of the result

  ifft(sig, N);

  // print out the results

  std::cout << "cross correlation output." << std::endl;
  std::cout << "we expect the refence signal to" << std::endl;
  std::cout << "move to the left by 3" << std::endl;
  std::cout << "or to the right by 7" << std::endl;

  for (int i = 0; i < N; i++)
    printf("%f\n", sig[i]);
  std::cout << std::endl;

  // zero out the signal

  for (int i = 0; i < N; i++)
    sig[i] = 0.0;

  // populate the signal with new data

  sig[6] = 1.0;

  fft(sig, N);

  // multiply the refence to the signal (Complex)

  for (int i = 0; i < N; i+=2) {
    tmp = sig[i]*ref[i] - sig[i+1]*ref[i+1];
    sig[i+1] = sig[i]*ref[i+1] + ref[i]*sig[i+1];
    sig[i] = tmp;
  }

  // take the inverse fft of the result

  ifft(sig, N);

  // print out the results

  std::cout << "cross correlation output." << std::endl;
  std::cout << "we expect the refence signal to" << std::endl;
  std::cout << "move to the right by 2" << std::endl;
  std::cout << "or to the left by 8" << std::endl;

  for (int i = 0; i < N; i++)
    printf("%f\n", sig[i]);
  std::cout << std::endl;

  // zero out the signal

  for (int i = 0; i < N; i++)
    sig[i] = 0.0;

  // populate the signal with new data

  sig[4] = 1.0;

  // take the FFT of the signal

  fft(sig, N);

  // multiply the refence to the signal (Complex)

  for (int i = 0; i < N; i+=2) {
    tmp = sig[i]*ref[i] - sig[i+1]*ref[i+1];
    sig[i+1] = sig[i]*ref[i+1] + ref[i]*sig[i+1];
    sig[i] = tmp;
  }

  // take the inverse fft of the result

  ifft(sig, N);

  // print out the results

  std::cout << "cross correlation output." << std::endl;
  std::cout << "we expect the refence signal to" << std::endl;
  std::cout << "already match the signal" << std::endl;

  for (int i = 0; i < N; i++)
    printf("%f\n", sig[i]);
  std::cout << std::endl;

  return 0;
}
