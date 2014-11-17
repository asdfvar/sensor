/*
 *
 * main for matched filter
 *
 */

#include "mflt.h"
#include <iostream>
extern "C" {
#include "fft.h"
}

int matchedfilter(void) {

  float *data = new float[20];

  for (int k = 0; k < 20; k++)
     data[k] = (float)k;

//  mflt::FFT(data, 20);
//   fft(data, 20);

  for (int k = 0; k < 20; k++)
     std::cout << data[k] << std::endl;

  std::cout << "hey there" << std::endl;
  return 0;

}
