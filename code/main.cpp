#include <iostream>
#include "mf_main.h"
#include "fileio.h"
#include "ref.h"

extern "C" {
#include "fft.h"
}

int main() {

   const std::string kin_data_path = "../data/Craig_Walking_tredmil.csv";
   const std::string ref_walking = "../data/craig_walking_tredmil_reference_signals.csv";

#if 0
   int N_all_pts = fio::count_kinetisense_lines( kin_data_path.c_str() );
   float **sens_data = fio::read_kinetisense( kin_data_path.c_str() );
#endif

   fio KIN( kin_data_path.c_str() );

   int ref_N;
   float ref_freq;
   float ref_time;

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

//   preproc ( ... );

//   matchedfilter ( ... );

//   neuralnetwork ( ... );

#if 0
   for (int k = 0; k < 20; k++)
     delete[] sens_data[k];
#endif

   delete[] ref_data_primary;
   delete[] ref_data_secondary;

for (int k = 0; k < 512; k++ )
   std::cout << ref_data_primary[k] << std::endl;

std::cout << "Hello" << std::endl;
   return 0;
}
