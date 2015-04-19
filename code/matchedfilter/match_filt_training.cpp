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
              bool           Do_taper,
              float          cutoff_freq,
              float          freq_range,
              float          samp_freq,
              float          dt,
              float          time_window,      /* Signal window time (seconds)    */
              int            N_window,         /* Signal window points (elements) */
              float          time_window_ref,  /* Reference length (seconds)      */
              int            N_window_ref,     /* Reference length (# elements)   */
              int            sens_num)         /* Which Kinetesense sensor        */
{

 float time_inc = (KIN->get_total_time() - time_window) / BINS;

 float start_time_ref  = 0.0;
 float best_start_time = start_time_ref;
 float start_time_sig  = 0.0;

 float sum_corr          = 0.0;
 float best_correlations = 0.0;

 float *__restrict__ ax = new float[N_window+2];   // Workspace for the signal in x
 float *__restrict__ ay = new float[N_window+2];   // Workspace for the signal in y
 float *__restrict__ az = new float[N_window+2];   // Workspace for the signal in z

 float *__restrict__ buf = new float[N_window+2];
 float *__restrict__ tmp;

 float prev_perc_done = 0.0;
 float curr_perc_done = 0.0;

 float power;

 gettime();

 while (KIN->valid_start_end (start_time_ref, time_window))
 {

    /* load into reference */

    tmp = KIN->get_sens_ax (start_time_ref, sens_num);
    for (int k=0; k<N_window+2; k++) ax[k] = tmp[k];

    tmp = KIN->get_sens_ay (start_time_ref, sens_num);
    for (int k=0; k<N_window+2; k++) ay[k] = tmp[k];

    tmp = KIN->get_sens_az (start_time_ref, sens_num);
    for (int k=0; k<N_window+2; k++) az[k] = tmp[k];

    preproc(
        ax,            /* Acceleration data in x               */
        ay,            /* Acceleration data in y               */
        az,            /* Acceleration data in z               */
        &power,        /* Resulting power of the signal        */
        dt,            /* Delta time comstant                  */
        time_window,   /* Time window of the data              */
        samp_freq,     /* Sampling frequency of the data       */
        N_window);     /* Number of sample points              */

    MF->load_ref (ax, ay, dt, samp_freq, time_window_ref, N_window_ref, N_window);
    if (Do_taper) MF->apply_taper (buf, cutoff_freq, freq_range);
    MF->apply_fft(N_window);

    /* Loop through signal to test this loaded reference */

    start_time_sig = 0.0;
    sum_corr       = 0.0;
    while (KIN->valid_start_end (start_time_sig, time_window))
    {

       tmp = KIN->get_sens_ax (start_time_sig, sens_num);
       for (int k=0; k<N_window+2; k++) ax[k] = tmp[k];

       tmp = KIN->get_sens_ay (start_time_sig, sens_num);
       for (int k=0; k<N_window+2; k++) ay[k] = tmp[k];

       tmp = KIN->get_sens_az (start_time_sig, sens_num);
       for (int k=0; k<N_window+2; k++) az[k] = tmp[k];

       preproc(
           ax,            /* Acceleration data in x               */
           ay,            /* Acceleration data in y               */
           az,            /* Acceleration data in z               */
           &power,        /* Resulting power of the signal        */
           dt,            /* Delta time comstant                  */
           time_window,   /* Time window of the data              */
           samp_freq,     /* Sampling frequency of the data       */
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

       sum_corr += MF->get_corr_ax () * MF->get_corr_ay() ;

       start_time_sig += time_inc;

    }
    if (sum_corr > best_correlations) {
       best_correlations = sum_corr;
       best_start_time = start_time_ref;
    }

    curr_perc_done = start_time_ref/(KIN->get_total_time() - time_window)*100.0;
    if (curr_perc_done - prev_perc_done > 10.0) {
       std::cout << "Training " << curr_perc_done << "% done" << std::endl;
       prev_perc_done = curr_perc_done;
    }

    start_time_ref += time_inc;
 }

 /* load the best section into the reference */

 std::cout << "Reference choosen from start time: " << best_start_time << " From "
           << KIN->get_total_time() << " Total seconds of data" << std::endl;

 tmp = KIN->get_sens_ax (best_start_time, sens_num);
 for (int k=0; k<N_window+2; k++) ax[k] = tmp[k];

 tmp = KIN->get_sens_ay (best_start_time, sens_num);
 for (int k=0; k<N_window+2; k++) ay[k] = tmp[k];

 tmp = KIN->get_sens_az (best_start_time, sens_num);
 for (int k=0; k<N_window+2; k++) az[k] = tmp[k];

 preproc(
     ax,            /* Acceleration data in x               */
     ay,            /* Acceleration data in y               */
     az,            /* Acceleration data in z               */
     &power,        /* Resulting power of the signal        */
     dt,            /* Delta time comstant                  */
     time_window,   /* Time window of the data              */
     samp_freq,     /* Sampling frequency of the data       */
     N_window);     /* Number of sample points              */

 MF->load_ref (ax, ay, dt, samp_freq, time_window_ref, N_window_ref, N_window);

 std::cout << "Training time = " << gettime() << std::endl;

 delete[] ax;
 delete[] ay;
 delete[] az;
 delete[] buf;

}
