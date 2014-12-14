#include "mf_main.h"
#include "fileio.h"
extern "C" {
#include "fft.h"
}
#include <iostream>

int main() {

   const std::string kin_data_path = "../data/Craig_Walking_tredmil.csv";
   const std::string ref_walking = "../data/Craig_walking_signal_primary_axis.csv";

   int N_all_pts = fio::count_kinetisense_lines( kin_data_path.c_str() );
   float **sens_data = fio::read_kinetisense( kin_data_path.c_str() );

   int ref_N;
   float ref_freq;
   float ref_time;

   fio::read_reference_headers (
                        ref_walking.c_str(),
                        &ref_N,
                        &ref_freq,
                        &ref_time);

   float *ref_data = new float[ref_N];

   fio::read_reference (ref_walking.c_str(),
                        ref_data,
                        ref_N);

//   preproc ( ... );

//   matchedfilter ( ... );

//   neuralnetwork ( ... );

   for (int k = 0; k < 20; k++)
     delete[] sens_data[k];

   delete[] ref_data;

for (int k = 0; k < 512; k++ )
   std::cout << ref_data[k] << std::endl;

std::cout << "Hello" << std::endl;
   return 0;
}
