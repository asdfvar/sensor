#include "fileio.h"

fio::fio (const char path[] )
{

   N        = count_kinetisense_lines( path );
   kin_data = read_kinetisense( path );

}

/******************************************************************/

fio::~fio ()
{

   for (int k = 0; k < 20; k++)
     delete[] kin_data[k];

}

/******************************************************************/

bool fio::valid_start_end (int start, int N_count)
{
   if ( start + N_count > N ) return false;
   else return true;
}

/******************************************************************/

float *fio::get_sens1_ax (void)
{
   return kin_data[0];
}

/******************************************************************/

float *fio::get_sens1_ay (void)
{
   return kin_data[1];
}

/******************************************************************/

float *fio::get_sens1_az (void)
{
   return kin_data[2];
}

/******************************************************************/

float *fio::get_sens2_ax (void)
{
   return kin_data[6];
}

/******************************************************************/

float *fio::get_sens2_ay (void)
{
   return kin_data[7];
}

/******************************************************************/

float *fio::get_sens2_az (void)
{
   return kin_data[8];
}
