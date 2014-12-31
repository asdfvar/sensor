#include "matchedfilter.h"
#include <iostream>

/******************************************************************************/

matchedfilter::matchedfilter (void)
{

   loaded_ref = false;

}

/******************************************************************************/

matchedfilter::~matchedfilter (void)
{

   if (loaded_ref) {
      delete[] ref_ax;
      delete[] ref_ay;
   }

}

/******************************************************************************/

void matchedfilter::load_ref (float *ref_ax_in, float *ref_ay_in, float dt_in,
                              float samp_freq_in, float time_window_in,
                              int N_data_in, int N_window_in,
                              float *work_buffer_in)
{

   /* Tell itself that it has the reference data now */
   loaded_ref = true;

   ref_ax          = ref_ax_in;
   ref_ay          = ref_ay_in;
   dt_ref          = dt_in;
   time_window_ref = time_window_in;
   samp_freq_ref   = samp_freq_in;
   N_data_ref      = N_data_in;
   N_window_ref    = N_window_in;
   work_buffer     = work_buffer_in;

}

/******************************************************************************/

void matchedfilter::run (float *sig_ax, float *sig_ay, float dt_sig, float samp_freq_sig, int N_sig,
                         float *corr_ax, float *corr_ay)
{

   int shift; // Shift in cells between the reference and the signal to match

   if (!loaded_ref) {
      std::cout << "Error: Did not load the reference signal" << std::endl;
      return;
   }

   if (dt_sig != dt_ref) {
      std::cout << "Error: Reference and signal delta time measurements do not match" << std::endl;
      return;
   }

   if (samp_freq_sig != samp_freq_ref) {
      std::cout << "Error: Reference and signal sampling frequencies do not match" << std::endl;
      return;
   }

   if (N_sig != N_data_ref) {
      std::cout << "Error: Reference and signal do not have the same allocated space" << std::endl;
      return;
   }

   crosscorr(ref_ax, sig_ax, work_buffer, dt_sig, samp_freq_sig,
             N_window_ref, N_sig, corr_ax, &shift);

   crosscorr(ref_ay, sig_ay, work_buffer, dt_sig, samp_freq_sig,
             N_window_ref, N_sig, corr_ay, &shift);

}

/******************************************************************************/
