#include "matchedfilter.h"
#include "run_mf.h"
#include "fileio.h"
#include "preproc.h"
#include "gettime.h"
#include "taper.h"
#include "filter.h"
#include <iostream>

#define BINS 200.0

void match_filt_training(
              matchedfilter *MF,
              fio::kinIO    *KIN,
              float         *taper,
              fio::parameters *PARAMETERS,
              int            sens_num)         /* Which Kinetesense sensor        */
{

 bool  Do_taper        = PARAMETERS->Do_taper();
 float cutoff_freq     = PARAMETERS->get_cutoff_freq();
 float freq_range      = PARAMETERS->get_freq_range();
 float samp_freq       = PARAMETERS->get_samp_freq();
 float dt              = PARAMETERS->get_dt();
 float time_window     = PARAMETERS->get_time_window();      /* Signal window time (seconds)    */
 int   N_window        = PARAMETERS->get_N_window();         /* Signal window points (elements) */
 float time_window_ref = PARAMETERS->get_time_window_ref();  /* Reference length (seconds)      */
 int   N_window_ref    = PARAMETERS->get_N_window_ref();     /* Reference length (# elements)   */
 int   count;
 
 float time_inc = (KIN->get_total_time() - time_window) / BINS;

 float start_time_ref  = 0.0;
 float best_start_time = start_time_ref;
 float start_time_data  = 0.0;

 float sum_corr          = 0.0;
 float best_correlation = 0.0;

 float *__restrict__ ax = new float[N_window+2];   // Workspace for the signal in x
 float *__restrict__ ay = new float[N_window+2];   // Workspace for the signal in y
 float *__restrict__ az = new float[N_window+2];   // Workspace for the signal in z

 float *__restrict__ buf = new float[N_window+2];

 float prev_perc_done = 0.0;
 float curr_perc_done = 0.0;

 float power;

 gettime();

 while (KIN->valid_start_end (start_time_ref, time_window))
 {

    /* load into reference */

    KIN->load_sens_ax (ax, start_time_ref, 2, N_window);
    KIN->load_sens_ay (ay, start_time_ref, 2, N_window);
    KIN->load_sens_az (az, start_time_ref, 2, N_window);

    preproc(
        ax,            /* Acceleration data in x               */
        ay,            /* Acceleration data in y               */
        az,            /* Acceleration data in z               */
        &power,        /* Resulting power of the signal        */
        PARAMETERS,    /* Sampling frequency of the data       */
        N_window);     /* Number of sample points              */

    MF->load_ref (ax, ay, dt, samp_freq, time_window_ref, N_window_ref, N_window);
    if (Do_taper) MF->apply_taper (buf, cutoff_freq, freq_range);
    MF->apply_fft(N_window);

    /* Loop through signal to test this loaded reference */

    for (count           = 0,
         start_time_data = 0.0f,
         sum_corr        = 0.0f;
            KIN->valid_start_end (start_time_data, time_window);
               count++)
    {

       KIN->load_sens_ax (ax, start_time_data, 2, N_window);
       KIN->load_sens_ay (ay, start_time_data, 2, N_window);
       KIN->load_sens_az (az, start_time_data, 2, N_window);

       preproc(
           ax,            /* Acceleration data in x               */
           ay,            /* Acceleration data in y               */
           az,            /* Acceleration data in z               */
           &power,        /* Resulting power of the signal        */
           PARAMETERS,    /* Sampling frequency of the data       */
           N_window);     /* Number of sample points              */

       if (Do_taper) {
#if 0
          apply_taper (ax, taper, N_window);
          apply_taper (ay, taper, N_window);
#else
          apply_filter (ax, 1, N_window);
          apply_filter (ay, 1, N_window);
#endif
       }

       run_mf (MF,
               ax,
               ay,
               dt,
               samp_freq,
               N_window,
               buf);

       sum_corr += MF->get_correlation();

       start_time_data += time_inc;

    }

    float ave_correlation = sum_corr / (float)count;

    if (ave_correlation > best_correlation) {
       best_correlation = ave_correlation;
       best_start_time   = start_time_ref;
    }

    curr_perc_done = start_time_ref/(KIN->get_total_time() - time_window)*100.0f;
    if (curr_perc_done - prev_perc_done >= 10.0f)
    {

       std::cout << "Training "            <<
                    curr_perc_done         <<
                    "% done. "             <<
                    "this average corr = " <<
                    ave_correlation        <<
                    " best correlation = " <<
                    best_correlation       <<
                    " best time = "        <<
                    best_start_time        <<
                    std::endl;

       prev_perc_done = curr_perc_done;
    }

    start_time_ref += time_inc;
 }

 /* load the best section into the reference */

 std::cout << "Reference choosen from start time: " << best_start_time << " From "
           << KIN->get_total_time() << " Total seconds of data" << std::endl;

 KIN->load_sens_ax (ax, best_start_time, 2, N_window);
 KIN->load_sens_ay (ay, best_start_time, 2, N_window);
 KIN->load_sens_az (az, best_start_time, 2, N_window);

 preproc(
     ax,            /* Acceleration data in x               */
     ay,            /* Acceleration data in y               */
     az,            /* Acceleration data in z               */
     &power,        /* Resulting power of the signal        */
     PARAMETERS,    /* Sampling frequency of the data       */
     N_window);     /* Number of sample points              */

 MF->load_ref (ax, ay, dt, samp_freq, time_window_ref, N_window_ref, N_window);

 std::cout << "Training time = " << gettime() << std::endl;

 delete[] ax;
 delete[] ay;
 delete[] az;
 delete[] buf;

}
