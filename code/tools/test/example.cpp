#include <iostream>
#include "fileio.h"

int main() {

const std::string kin_data_path = "../../../data/Craig_Walking_tredmil.csv";
   const std::string ref_walking = "../../../data/Craig_walking_signal_primary_axis.csv";

   int N_all_pts = fio::count_kinetisense_lines( kin_data_path.c_str() );
   float **sens_data = fio::read_kinetisense( kin_data_path.c_str() );

   float *ref_data = fio::read_reference ( ref_walking.c_str() );

   for (int k = 0; k < 20; k++)
     delete[] sens_data[k];

   delete[] ref_data;

   for (int k = 0; k < 512; k++ )
      std::cout << ref_data[k] << std::endl;

   return 0;
}
