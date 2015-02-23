#include "matchedfilter.h"
#include "fileio.h"
#include "preproc.h"
#include "gettime.h"
#include <iostream>

#define BINS 200.0

void match_filt_training(
              matchedfilter *MF,
              fio::kinIO    *KIN,
              float         *taper,
              bool           apply_taper,
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

 float *ax = new float[N_window+2];   // Workspace for the signal in x
 float *ay = new float[N_window+2];   // Workspace for the signal in y
 float *az = new float[N_window+2];   // Workspace for the signal in z

 float *work_buf = new float[N_window+2];
 float *tmp;

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

       MF->run (ax, ay, dt, samp_freq, N_window, taper, apply_taper, work_buf);

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
 MF->apply_fft(N_window);

 std::cout << "Training time = " << gettime() << std::endl;

 delete[] ax;
 delete[] ay;
 delete[] az;
 delete[] work_buf;

}
