#include <iostream>
#include "fileio.h"
#include "ref.h"

int main() {

   const std::string kin_data_path = "../../../../data/Craig_Walking_tredmil.csv";
   const std::string ref_walking = "../../../../data/craig_walking_tredmil_reference_signals.csv";

   fio KIN ( kin_data_path.c_str() );

   // Populate sens1_ax with acceleration data in x
   float *sens1_ax;

   float start = 0.0;
   float window = 4.0;
   int N = (int) (window * 128.0);
   do {

      sens1_ax = KIN.get_sens1_ax ( start );

      if ( start == 20.0)
      for (int k = 0; k < N; k++)
         std::cout << sens1_ax[k] << std::endl;

      start += 0.5;

   } while (KIN.valid_start_end (start, window));

   // Read in the reference data
   int ref_N;
   float ref_freq, ref_time;

   ref::read_reference_headers (
                        ref_walking.c_str(),
                        &ref_N,
                        &ref_freq,
                        &ref_time);

   float *ref_data_primary = new float[ref_N];
   float *ref_data_secondary = new float[ref_N];

   ref::read_reference (ref_walking.c_str(),
                        ref_data_primary,
                        ref_data_secondary,
                        ref_N);

   std::cout << "N = " << ref_N
             << " freq = " << ref_freq
             << " time = " << ref_time << std::endl;

   std::cout << "Primary reference signal:" << std::endl;
   for (int k = 0; k < 8; k++)
      std::cout << ref_data_primary[k] << std::endl;

   std::cout << "Secondary reference signal:" << std::endl;
   for (int k = 0; k < 8; k++)
      std::cout << ref_data_secondary[k] << std::endl;

   delete[] ref_data_primary;
   delete[] ref_data_secondary;

   return 0;
}
