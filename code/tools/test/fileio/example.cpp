#include <iostream>
#include "fileio.h"
#include "ref.h"

int main() {

   const std::string kin_data_path = "../../../../data/Craig_Walking_tredmil.csv";
   const std::string ref_walking = "../../../../data/Craig_walking_signal_primary_axis.csv";

   fio KIN ( kin_data_path.c_str() );

   // populate sens1_ax with acceleration data in x
   float *sens1_ax = KIN.get_sens1_ax ();

   int start = 0;
   int N = 10;
   do {

      if ( start == 20 )
      for (int k = 0; k < N; k++)
         std::cout << sens1_ax[ start + k ] << std::endl;

      start += N;

   } while (KIN.valid_start_end (start, N));

   int ref_N;
   float ref_freq, ref_time;

   ref::read_reference_headers (
                        ref_walking.c_str(),
                        &ref_N,
                        &ref_freq,
                        &ref_time);

   float *ref_data = new float[ref_N];

   ref::read_reference (ref_walking.c_str(),
                        ref_data,
                        ref_N);

   std::cout << "N = " << ref_N
             << " freq = " << ref_freq
             << " time = " << ref_time << std::endl;

   for (int k = 0; k < 8; k++)
      std::cout << ref_data[k] << std::endl;

   delete[] ref_data;

   return 0;
}
