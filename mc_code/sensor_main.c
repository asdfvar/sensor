#include "sensor.h"
#include "preproc.h"
#include "run_mf.h"

void sensor_main(
 /*[I ]*/ const float sampling_freq,     /* Sampling frequency                        */
 /*[I ]*/ const float data_time_length,  /* data time length in seconds               */
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

   int k, p;

   float dt = 1.0f / sampling_freq;
   const int   N_window = (int)(sampling_freq * data_time_length);

   float *workspace_float = (float*)workspace;

   float *ref_buffer_x    = workspace_float; workspace_float += N_window + 2;
   float *ref_buffer_y    = workspace_float; workspace_float += N_window + 2;

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
        N_window);     /* Number of sample points              */

   float max_correlation = -1.0f;

   for (k = 0; k < num_references; k++)
   {

      for (p = 0; p < N_window; p++) ref_buffer_x[p] = 0.0f;
      for (p = 0; p < N_window; p++) ref_buffer_y[p] = 0.0f;
      
      /*
      ** MATCHED-FILTER
      */
#if 1
      float correlation =
                     run_mf(
                        ax,
                        ay,
                        ref_buffer_x,
                        ref_buffer_y,
                        dt,
                        data_time_length,
                       *ref_time_length,
                        sampling_freq,
                        workspace_float);
#endif

   }

   return;
}
