#include "sensor.h"
#include "preproc.h"

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
 /*[I ]*/ float      *references,        /* References                                */
 /*[ O]*/ float      *energy,            /* Energy                                    */
 /*[ O]*/ float      *correlations,      /* Correlations for each of the references   */
 /*[ O]*/ float      *power,             /* Signal power                              */
 /*[ O]*/ int        *activity,          /* Determined activity                       */
 /*[  ]*/ void       *workspace)         /* pre-allocated buffer space. Size = TBD    */
{

   float *workspace_float = (float*)workspace;

   float dt = 1.0f / sampling_freq;
   const int   N_window = (int)(sampling_freq * data_time_length);

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

   return;
}
