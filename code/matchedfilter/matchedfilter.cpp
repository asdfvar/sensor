#include "matchedfilter.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

#define N_headers 3

/******************************************************************************/

matchedfilter::matchedfilter (const char path[], int N_data)
{

   N_data_ref = N_data;

   ref_ax = new float[N_data_ref+2];
   for (int k=0; k<N_data_ref+2; k++) ref_ax[k] = 0.0;

   ref_ay = new float[N_data_ref+2];
   for (int k=0; k<N_data_ref+2; k++) ref_ay[k] = 0.0;

   std::string line;
   std::string name;
   std::string value;
   std::string delimiter = "=";
   std::ifstream ref_file;

   ref_file.open (path);
   ref_file.seekg( 0 );

   // read the headers
   for (int k=0; k<N_headers; k++) {
      std::getline ( ref_file, line );

      name = line.substr(0, line.find(delimiter));
      value = line.substr(line.find(delimiter)+1, line.length() );

      if (name.compare("N ") == 0)              N_window_ref    = atoi(value.c_str());
      else if (name.compare("frequency ") == 0) samp_freq_ref   = atof(value.c_str());
      else if (name.compare("time ") == 0)      time_window_ref = atof(value.c_str());
   }

   dt_ref = 1.0 / samp_freq_ref;

   ref_file.seekg(0);

   // read past the headers
   for (int k=0; k<N_headers; k++)
      std::getline ( ref_file, line );

   for ( int k = 0; k < N_window_ref; k++ ) {
      std::getline ( ref_file, line, ',' );
      ref_ax[k] = atof ( line.c_str() );
   }

   // read past the headers
   for (int k=0; k<N_headers+1; k++)
      std::getline ( ref_file, line );

   for ( int k = 0; k < N_window_ref; k++ ) {
      std::getline ( ref_file, line, ',' );
      ref_ay[k] = atof ( line.c_str() );
   }

   ref_file.close();

   correlations_computed = false;

}

/******************************************************************************/

matchedfilter::~matchedfilter (void)
{

   delete[] ref_ax;
   delete[] ref_ay;

}

/******************************************************************************/

void matchedfilter::load_ref (float *ref_ax_in, float *ref_ay_in, float dt_in,
                              float samp_freq_in, float time_window_in,
                              int N_data_in, int N_window_in,
                              float *work_buffer_in)
{

   ref_ax          = ref_ax_in;
   ref_ay          = ref_ay_in;
   dt_ref          = dt_in;
   time_window_ref = time_window_in;
   samp_freq_ref   = samp_freq_in;
   N_data_ref      = N_data_in;
   N_window_ref    = N_window_in;

}

/******************************************************************************/

int matchedfilter::run (float *sig_ax, float *sig_ay, float dt_sig, float samp_freq_sig, int N_sig,
                         float *work_buffer)
{

   if (dt_sig != dt_ref) {
      std::cout << "Error: Reference and signal delta time measurements do not match" << std::endl;
      return -1;
   }

   if (samp_freq_sig != samp_freq_ref) {
      std::cout << "Error: Reference and signal sampling frequencies do not match" << std::endl;
      return -1;
   }

   if (N_sig != N_data_ref) {
      std::cout << "Error: Reference and signal do not have the same allocated space" << std::endl;
      return -1;
   }

   corr_ax = crosscorr(ref_ax, sig_ax, work_buffer, dt_sig, samp_freq_sig,
                        N_window_ref, N_sig, TIME);

   corr_ay = crosscorr(ref_ay, sig_ay, work_buffer, dt_sig, samp_freq_sig,
                        N_window_ref, N_sig, TIME);

   correlations_computed = true;

}

/******************************************************************************/

float matchedfilter::get_corr_ax (void)
{
   if (correlations_computed) {
      return corr_ax;
   } else {
      std::cout << "Error: Correlations not computed yet" << std::endl;
      return -1;
   }
}

/******************************************************************************/

float matchedfilter::get_corr_ay (void)
{
   if (correlations_computed) {
      return corr_ay;
   } else {
      std::cout << "Error: Correlations not computed yet" << std::endl;
      return -1;
   }
}

/******************************************************************************/
