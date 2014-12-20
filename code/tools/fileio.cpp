#include "fileio.h"

fio::fio (const char path[] )
{

   N        = count_kinetisense_lines( path );
   samp_freq = 128.0; // Hz
   kin_data = read_kinetisense( path );
   total_time = (float)N / samp_freq;

}

/******************************************************************/

fio::~fio ()
{

   for (int k = 0; k < 20; k++)
     delete[] kin_data[k];

}

/******************************************************************/

bool fio::valid_start_end (float start, float window)
{
   if ( start + window > total_time ) return false;
   else return true;
}

/******************************************************************/

float *fio::get_sens1_ax (float time)
{
   int k = (int)(time * samp_freq);
   return kin_data[0] + k;
}

/******************************************************************/

float *fio::get_sens1_ay (float time)
{
   return kin_data[1] + (int)(time * samp_freq);
}

/******************************************************************/

float *fio::get_sens1_az (float time)
{
   return kin_data[2] + (int)(time * samp_freq);
}

/******************************************************************/

float *fio::get_sens2_ax (float time)
{
   return kin_data[6] + (int)(time * samp_freq);
}

/******************************************************************/

float *fio::get_sens2_ay (float time)
{
   return kin_data[7] + (int)(time * samp_freq);
}

/******************************************************************/

float *fio::get_sens2_az (float time)
{
   return kin_data[8] + (int)(time * samp_freq);
}
