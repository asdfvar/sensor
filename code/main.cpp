#include "matchedfilter.h"
extern "C" {
#include "fft.h"
}

int main() {

   matchedfilter();

   float *data = new float[20];

 for (int k = 0; k < 20; k++)
     data[k] = (float)k;

   fft(data, 20);

   return 0;
}
