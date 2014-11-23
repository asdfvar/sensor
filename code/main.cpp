#include "mf_main.h"
#include "kinetisense.h"
extern "C" {
#include "fft.h"
}
#include <iostream>

int main() {

   const std::string kin_data_path = "../data/Craig_Walking_tredmil.csv";

   int N_all_pts = count_kinetisense_lines( kin_data_path.c_str() );
   float **sens_data = read_kinetisense( kin_data_path.c_str() );

//   preproc ( ... );

//   matchedfilter ( ... );

//   ann ( ... );

   for (int k = 0; k < 20; k++)
     delete[] sens_data[k];

std::cout << "Hello" << std::endl;
   return 0;
}
