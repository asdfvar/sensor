#include "mf_main.h"
extern "C" {
#include "fft.h"
}

int main() {

   matchedfilter();

   float *data = new float[20];
   delete[] data;

   return 0;
}
