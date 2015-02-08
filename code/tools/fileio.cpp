#include "fileio.h"
#include <iostream>
#include <fstream>

namespace fio {
 kinIO::kinIO (const char path[] )
 {

   N          = count_kinetisense_lines( path );
   samp_freq  = 128.0; // Hz
   kin_data   = read_kinetisense( path );
   total_time = (float)N / samp_freq;

 }

/******************************************************************/

 kinIO::~kinIO ()
 {

   for (int k = 0; k < 20; k++)
     delete[] kin_data[k];

 }

/******************************************************************/

 bool kinIO::valid_start_end (float start, float window)
 {
   if ( start + window > total_time ) return false;
   else return true;
 }

/******************************************************************/

 float *kinIO::get_sens_ax (float time, int sens_num)
 {
   int k = (int)(time * samp_freq);

   if (sens_num == 1) return kin_data[0] + k;
   else if (sens_num == 2) return kin_data[6] + k;
   else if (sens_num == 3) return kin_data[12] + k;
   else {
      std::cout << "Sensor number not supported" << std::endl;
      return 0;
   }
 }

/******************************************************************/

 float *kinIO::get_sens_ay (float time, int sens_num)
 {
   int k = (int)(time * samp_freq);

   if (sens_num == 1) return kin_data[1] + k;
   else if (sens_num == 2) return kin_data[7] + k;
   else if (sens_num == 3) return kin_data[13] + k;
   else {
      std::cout << "Sensor number not supported" << std::endl;
      return 0;
   }
 }

/******************************************************************/

 float *kinIO::get_sens_az (float time, int sens_num)
 {
   int k = (int)(time * samp_freq);

   if (sens_num == 1) return kin_data[2] + k;
   else if (sens_num == 2) return kin_data[8] + k;
   else if (sens_num == 3) return kin_data[17] + k;
   else {
      std::cout << "Sensor number not supported" << std::endl;
      return 0;
   }
 }

/******************************************************************/

 float kinIO::get_total_time (void)
 {
    return total_time;
 }

/******************************************************************/

 void write_val(float val, std::string out_file_path, std::string ID, bool init)
 {

   out_file_path += ID;
   std::ofstream out_file;
   if (init) {
      out_file.open (out_file_path.c_str());
      std::cout << "Writing data to " << out_file_path << std::endl;
   } else {
      out_file.open (out_file_path.c_str(), std::ios::app);
   }
   out_file << val << "\n";
   out_file.close();


 }

/******************************************************************/

 void write_val(int val, std::string out_file_path, std::string ID,  bool init)
 {

   out_file_path += ID;
   std::ofstream out_file;
   if (init) {
      out_file.open (out_file_path.c_str());
   } else {
      out_file.open (out_file_path.c_str(), std::ios::app);
   }
   out_file << val << "\n";
   out_file.close();

 }

/******************************************************************/

}
