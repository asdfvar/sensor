#include "sensor.h"
#include <stdlib.h>

enum {MALE = 1, FEMALE = 2};

int main()
{

   /*
   ** Outputs:
   */
   float energy;                   /* output. Energy */
   float correlations[2];          /* output. Correlations for each of the references */
   float power;                    /* output. Signal power */
   int   activity;                 /* output. Determined activity */

   const float sampling_freq = 100.0f; // Hz
   const float data_time_length = 4.0f; // seconds

   int data_num_elements = (int)(sampling_freq * data_time_length) + 2; // +2 for nyquist

   float *ax = malloc( data_num_elements * sizeof(*ax) );
   float *ay = malloc( data_num_elements * sizeof(*ay) );
   float *az = malloc( data_num_elements * sizeof(*az) );

   int sex = MALE;
   int age = 30;
   float weight = 68.0f; // kg
   float height = 175.0f; // cm

   float ref_time_length[2] = {1.5f, 1.2f}; // seconds
   const int reference_act_ids[2] = {17190, 1015}; // {waking, bicycling}
   const int num_references = 2;

   int num_ref_points = (int)((ref_time_length[0] + ref_time_length[1]) * num_references);

   float *references = malloc( num_ref_points * sizeof(*references) );
   float *workspace = malloc( 10 * data_num_elements * sizeof(*workspace) );

   sensor_main (
       sampling_freq,     /* Sampling frequency                        */
       data_time_length,  /* data time length in seconds               */
       ax,                /* Acceleration data in x                    */
       ay,                /* Acceleration data in x                    */
       az,                /* Acceleration data in x                    */
       sex,               /* male = 1, female = 2                      */
       age,               /* Age in years                              */
       weight,            /* Weight in kg                              */
       height,            /* Height in cm                              */
       ref_time_length,   /* Time lengths for the references           */
       reference_act_ids, /* Activity IDs for the references           */
       num_references,    /* Number of references                      */
       references,        /* References                                */
      &energy,            /* Energy                                    */
       correlations,      /* Correlations for each of the references   */
      &power,             /* Signal power                              */
      &activity,          /* Determined activity                       */
       workspace);        /* pre-allocated buffer space. Size = TBD    */

   return 0;
}
