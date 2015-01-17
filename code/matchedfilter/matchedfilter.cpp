#include "matchedfilter.h"
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <cmath>
extern "C" {
#include "fft.h"
}

#define N_headers 3

/******************************************************************************/

matchedfilter::matchedfilter (int N_data)
{

   N_data_ref = N_data;

   ref_ax = new float[N_data_ref+2];
   ref_ay = new float[N_data_ref+2];

   for (int k=0; k<N_data_ref+2; k++) {
      ref_ax[k] = 0.0;
      ref_ay[k] = 0.0;
   }

   correlations_computed = false;
   ref_data_form         = TIME;
   activity_ID = "0";
}

/******************************************************************************/

void matchedfilter::load_ref (float *ax_in, float *ay_in,
                              float dt_in, float samp_freq_in,
                              float time_window_in, int N_window_in, int N_data_in)
{

   N_data_ref      = N_data_in;
   N_window_ref    = N_window_in;
   time_window_ref = time_window_in;
   dt_ref          = dt_in;
   samp_freq_ref   = samp_freq_in;

   for (int k=0; k<N_window_ref; k++) {
      ref_ax[k] = ax_in[k];
      ref_ay[k] = ay_in[k];
   }

   for (int k=N_window_ref; k<N_data_ref; k++) {
      ref_ax[k] = 0.0;
      ref_ay[k] = 0.0;
   }

   /* Compute the norm of the reference signal */

   norm_ref_ax = 0.0;
   norm_ref_ay = 0.0;
   for (int k = 0; k < N_window_ref; k++){
      norm_ref_ax    += ref_ax[k]*ref_ax[k];
      norm_ref_ay    += ref_ay[k]*ref_ay[k];
   }
   norm_ref_ax = sqrtf( norm_ref_ax );
   norm_ref_ay = sqrtf( norm_ref_ay );

   fft(ref_ax, N_data_ref);
   fft(ref_ay, N_data_ref);

   ref_data_form         = FREQ;
}

/******************************************************************************/

matchedfilter::matchedfilter (const char path[], std::string activity_ID_in, int N_data)
{

   N_data_ref = N_data;
   activity_ID = activity_ID_in;

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

   ref_file.seekg(0);

   // read past the headers
   for (int k=0; k<N_headers+1; k++)
      std::getline ( ref_file, line );

   for (int k = 0; k < N_window_ref; k++ ) {
      std::getline ( ref_file, line, ',' );
      ref_ay[k] = atof ( line.c_str() );
   }

   ref_file.close();

   /* Compute the norm of the reference signal */

   norm_ref_ax = 0.0;
   norm_ref_ay = 0.0;
   for (int k = 0; k < N_window_ref; k++){
      norm_ref_ax    += ref_ax[k]*ref_ax[k];
      norm_ref_ay    += ref_ay[k]*ref_ay[k];
   }
   norm_ref_ax = sqrtf( norm_ref_ax );
   norm_ref_ay = sqrtf( norm_ref_ay );

   correlations_computed = false;

   fft(ref_ax, N_data_ref);
   fft(ref_ay, N_data_ref);

   ref_data_form         = FREQ;

}

/******************************************************************************/

matchedfilter::~matchedfilter (void)
{

   delete ref_ax;
   delete ref_ay;

}

/******************************************************************************/

void matchedfilter::set_ID(std::string activity_ID_in)
{
   activity_ID = activity_ID_in;
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

   corr_ax = crosscorr(ref_ax, sig_ax, norm_ref_ax, work_buffer, dt_sig, samp_freq_sig,
                        N_window_ref, N_sig, FREQ);

   corr_ay = crosscorr(ref_ay, sig_ay, norm_ref_ay, work_buffer, dt_sig, samp_freq_sig,
                        N_window_ref, N_sig, FREQ);

   correlations_computed = true;

   return 1;
}

/******************************************************************************/

float matchedfilter::get_corr_ax (void)
{
   if (correlations_computed) {
      return corr_ax;
   } else {
      std::cout << "Error: Correlations not computed yet" << std::endl;
      return -1.0;
   }
}

/******************************************************************************/

float matchedfilter::get_corr_ay (void)
{
   if (correlations_computed) {
      return corr_ay;
   } else {
      std::cout << "Error: Correlations not computed yet" << std::endl;
      return -1.0;
   }
}

/******************************************************************************/

bool matchedfilter::write (std::string ref_file)
{
   if (ref_data_form == FREQ) {
      ifft(ref_ax, N_data_ref);
      ifft(ref_ay, N_data_ref);
      ref_data_form         = TIME;
   }

   std::ofstream out_file;
   out_file.open (ref_file.c_str());
   out_file << "N = " << N_window_ref << "\n";
   out_file << "frequency = " << samp_freq_ref << "\n";
   out_file << "time = " << time_window_ref << "\n";
   for (int k=0; k<N_window_ref-1; k++) out_file << ref_ax[k] << ",";
   out_file << ref_ax[N_window_ref-1];
   out_file << "\n";
   for (int k=0; k<N_window_ref-1; k++) out_file << ref_ay[k] << ",";
   out_file << ref_ay[N_window_ref-1];
   out_file.close();

   std::cout << "Written reference data to: " << ref_file << std::endl;

   return true;
}

/******************************************************************************/

node::node ( matchedfilter *MF_in ) {
   MF   = MF_in;
   prev = 0;
   next = 0;
}


/******************************************************************************/

node::~node (void) {
   delete MF;
}

/******************************************************************************/

mf_list::mf_list (void) {
   N     = 0;
   first = last = NODE;
}

/******************************************************************************/
/*
 *               current
 *                  |
 *                  |
 *                  v
 *      <-> N-1 <-> N     N+1 <->
 *                  ^      ^
 *                  |      |
 *                  |      |
 *                  N'-----+
 */

void mf_list::insert (matchedfilter *MF) {

   if (N == 0) {
      NODE = new node (MF);
      first = last = NODE;
      NODE->prev   = 0;
      NODE->next   = 0;
   } else {
      node *CURR = NODE;
      if (CURR == first) {
         NODE = new node (MF);
         CURR->prev = NODE;
         NODE->next = CURR;
         NODE->prev = 0;
      } else {
         NODE = new node (MF);
         NODE->next = CURR;
         NODE->prev = CURR->prev;
         CURR->prev = NODE;
      }
   }

   N++;
}

/******************************************************************************/

node *mf_list::pop (void) {

   node *CURR = NODE;
   if (NODE == first) {
      NODE = CURR->next;
      first = NODE;
      if (NODE != 0) NODE->prev = CURR->prev;
   } else if (NODE == last) {
      NODE = CURR->prev;
      NODE->next = CURR->next;
   } else {
      NODE = CURR->next;
      NODE->prev = CURR->prev;
      CURR->prev->next = NODE;
   }

   if (N>0) {
      std::cout << "Removing activity from the list"
                << std::endl;
      N--;
   } else {
      std::cout << "No activities to remove" << std::endl;
   }

   return CURR;
}

/******************************************************************************/

void mf_list::goto_next (void) {
   if (NODE != last) NODE = NODE->next;
   else std::cout << "Attempting to advance to the next "
                  << "matched filter but already on the last one"
                  << std::endl;
}

/******************************************************************************/

bool mf_list::is_last (void) {
   if (NODE == last) return true;
   else return false;
}

/******************************************************************************/

void mf_list::goto_prev (void) {
   if (NODE != first) NODE = NODE->prev;
   else std::cout << "Attempting to go to the previous "
                  << "matched filter but already on the first one"
                  << std::endl;
}

/******************************************************************************/

void mf_list::goto_first (void) {
   NODE = first;
}

/******************************************************************************/

void mf_list::goto_last (void) {
   NODE = last;
}

/******************************************************************************/

void mf_list::append (matchedfilter *MF) {
   if (N == 0) insert (MF);
   else {
      node *NEWNODE = new node (MF);
      last->next = NEWNODE;
      NEWNODE->prev = last;
      last = NEWNODE;
      N++;
   }
}

/******************************************************************************/

mf_list::~mf_list (void) {
   std::cout << "Cleaning up the list of activities" << std::endl;
   while (N>0) delete pop();
}

/******************************************************************************/

matchedfilter *mf_list::get_MF (void) {
   return NODE->MF;
}
