#include "data.h"
extern "C" {
#include "fft.h"
}
#include <iostream>

DATA::DATA(
   float *data_in, /* Data */
   int N_in,       /* Number of elements that make up the data */
   float dt_in)
{

   data  = data_in;
   N     = N_in;
   dt    = dt_in;
   df    = 1.0 / ((float) N * dt);
   state = t_space;

}

void DATA::data_fft( void ) {

   // Ensure the data is in the correct state
   if (state == f_space) {
      std::cout << "Error, data is already in frequency" << std::endl;
      return;
   }

   fft (data, N);

   state = f_space; // set the state of this data
}

void DATA::data_ifft( void ) {

   // Ensure the data is in the correct state
   if (state == t_space) {
      std::cout << "Error, data is already in time" << std::endl;
      return;
   }

   ifft (data, N);

   state = f_space; // set the state of this data
}

/* Return the energy spectral density of the data */

float DATA::esd (void) {

   float sum = 0.0;

   if ( state == t_space ) {
      for ( int i = 0; i < N; i++ ) {
         sum += data[i]*data[i];
      }
      sum *= dt;
   }
   else if ( state == f_space ) {
      for ( int i = 0; i < N+1; i++ ) {
         sum += data[i]*data[i];
      }
      sum *= df;
   }

   return sum;
}

/* Destroy */

DATA::~DATA ( void ) {
   delete data;
}