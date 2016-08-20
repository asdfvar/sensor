#include "sensor.h"
#include "preproc.h"
#include "run_mf.h"
#include "down_sample.h"
#include "energy_expenditure.h"
#include <stdio.h>

void sensor_main(
 /*[I ]*/ float       sampling_freq,     /* Sampling frequency                        */
 /*[I ]*/ const float data_time_length,  /* data time length in seconds               */
 /*[I ]*/ const int   downsamp_fact,     /* downsampling factor                       */
 /*[I ]*/ const float time_inc,          /* Time increment for next energy calculation*/
 /*[I ]*/ float      *ax,                /* Acceleration data in x                    */
 /*[I ]*/ float      *ay,                /* Acceleration data in x                    */
 /*[I ]*/ float      *az,                /* Acceleration data in x                    */
 /*[I ]*/ int         sex,               /* male = 1, female = 2                      */
 /*[I ]*/ int         age,               /* Age in years                              */
 /*[I ]*/ const float weight,            /* Weight in kg                              */
 /*[I ]*/ const float height,            /* Height in cm                              */
 /*[I ]*/ float      *ref_time_length,   /* Time lengths for the references           */
 /*[I ]*/ const int  *reference_act_ids, /* Activity IDs for the references           */
 /*[I ]*/ const int   num_references,    /* Number of references                      */
 /*[I ]*/ float      *references_x,      /* References                                */
 /*[I ]*/ float      *references_y,      /* References                                */
 /*[ O]*/ float      *energy,            /* Energy                                    */
 /*[ O]*/ float      *correlations,      /* Correlations for each of the references   */
 /*[ O]*/ float      *power,             /* Signal power                              */
 /*[ O]*/ int        *activity,          /* Determined activity                       */
 /*[**]*/ void       *workspace)         /* pre-allocated buffer space. Size = TBD    */
{

   float *workspace_float = (float*)workspace;

   int ref_ind, p;

   float output_samp_freq;

   output_samp_freq = down_sample (ax,
                                   sampling_freq,
                                   data_time_length,
                                   downsamp_fact,
                                   workspace_float);

   output_samp_freq = down_sample (ay,
                                   sampling_freq,
                                   data_time_length,
                                   downsamp_fact,
                                   workspace_float);

   output_samp_freq = down_sample (az,
                                   sampling_freq,
                                   data_time_length,
                                   downsamp_fact,
                                   workspace_float);

   sampling_freq = output_samp_freq;

   float dt = 1.0f / sampling_freq;
   const int N_window = (int)(sampling_freq * data_time_length);
   const int N_freq_window = N_window + 2;

   float *current_reference_x = references_x;
   float *current_reference_y = references_y;
   float *ref_buffer_x = workspace_float; workspace_float += N_freq_window;
   float *ref_buffer_y = workspace_float; workspace_float += N_freq_window;
   int    N_data = (int)(data_time_length * sampling_freq);

   /*
   ** PRE-PROCESSING
   */
   preproc (
        ax,            /* Acceleration data in x               */
        ay,            /* Acceleration data in y               */
        az,            /* Acceleration data in z               */
        power,         /* Resulting power of the signal        */
        dt,
        data_time_length,
        workspace_float,
        N_window);     /* Number of sample points              */

   float best_correlation = -1.0f;
   int   best_activity    =  0;

   for (ref_ind = 0; ref_ind < num_references; ref_ind++)
   {

      for (p = 0; p < N_freq_window; p++) ref_buffer_x[p] = 0.0f;
      for (p = 0; p < N_freq_window; p++) ref_buffer_y[p] = 0.0f;

      for (p = 0; p < N_freq_window; p++) ref_buffer_x[p] = current_reference_x[p];
      for (p = 0; p < N_freq_window; p++) ref_buffer_y[p] = current_reference_y[p];

      /*
      ** MATCHED-FILTER
      */
      float correlation =
                     run_mf(
                        ax,
                        ay,
                        ref_buffer_x,
                        ref_buffer_y,
                        dt,
                        data_time_length,
                        ref_time_length[ref_ind],
                        sampling_freq,
                        workspace_float);

printf("correlation = %f\n", correlation);

      if (correlation > best_correlation)
      {
         best_correlation = correlation;
         best_activity = activity[ref_ind];
      }

      current_reference_x += N_freq_window;
      current_reference_y += N_freq_window;

   }

   float energy_rate = energy_expenditure(
                         weight,
                         height,
                         age,
                         sex,
                         best_activity,
                        *power);

   *energy = energy_rate * time_inc;

   return;
}
