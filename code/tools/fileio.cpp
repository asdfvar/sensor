#include "fileio.h"

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
 }

/******************************************************************/

 float *kinIO::get_sens_ay (float time, int sens_num)
 {
   int k = (int)(time * samp_freq);

   if (sens_num == 1) return kin_data[1] + k;
   else if (sens_num == 2) return kin_data[7] + k;
 }

/******************************************************************/

 float *kinIO::get_sens_az (float time, int sens_num)
 {
   int k = (int)(time * samp_freq);

   if (sens_num == 1) return kin_data[2] + k;
   else if (sens_num == 2) return kin_data[8] + k;
 }

/******************************************************************/

 float kinIO::get_total_time (void)
 {
    return total_time;
 }

/******************************************************************/
}
