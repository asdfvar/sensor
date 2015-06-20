#include <string>
#include <fstream>
#include <iostream>

namespace fio {

 /*
  * Function NAME: write_correlations
  */
 void write_correlations(const std::string path, float *corr_ax, float *corr_ay, int N) {

   std::ofstream OF;
   OF.open (path.c_str());

   for (int k=0; k<N; k++) {
      OF << corr_ax[k] << "," << corr_ay[k] << "\n";
   }

   OF.close();

   std::cout << "Written correlation data to " << path << std::endl;

 }
}
