#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include "unit_test.h"

#define PI 3.14159265358979323f
#define TWO_PI 6.283185307179586f

enum {MALE = 1, FEMALE = 2};

int main()
{

   int k;

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
   float time_inc  = 1.5; // seconds

   int num_ref_points = (int)((ref_time_length[0] + ref_time_length[1]) * sampling_freq);

   float *references_x = malloc( num_ref_points * sizeof(*references_x) );
   float *references_y = malloc( num_ref_points * sizeof(*references_y) );
   void *workspace = malloc( 10 * data_num_elements * sizeof(float) );

   sinwave(
       ax,
       TWO_PI*4.0f, // omega
       0.0f,        // phase
       1.0f,        // amplitude
       data_time_length,
       sampling_freq);

   sinwave(
       ay,
       TWO_PI*4.0f,
       0.0f,
       1.0f,
       data_time_length,
       sampling_freq);

   sinwave(
       az,
       TWO_PI*4.0f,
       0.0f,
       0.0f,
       data_time_length,
       sampling_freq);

   sinwave(
       references_x,
       TWO_PI*4.0f,
       0.0f,
       1.0f,
       ref_time_length[0],
       sampling_freq);

   sinwave(
       references_y,
       TWO_PI*4.0f,
       0.0f,
       0.0f,
       ref_time_length[0],
       sampling_freq);

   sinwave(
       references_x + (int)(ref_time_length[0] * sampling_freq),
       TWO_PI*4.0f,
       0.0f,
       1.0f,
       ref_time_length[1],
       sampling_freq);

   sinwave(
       references_y + (int)(ref_time_length[0] * sampling_freq),
       TWO_PI*4.0f,
       0.0f,
       1.0f,
       ref_time_length[1],
       sampling_freq);

#if 0
   srand(0);

   for (k = 0; k < (int)(data_time_length*sampling_freq); k++)
   {
      ax[k] = (float)rand() / (float)RAND_MAX;
      ay[k] = (float)rand() / (float)RAND_MAX;
      az[k] = (float)rand() / (float)RAND_MAX;
   }
   printf("\n");
#endif

   sensor_main (
       sampling_freq,     /* Sampling frequency                        */
       data_time_length,  /* Data time length in seconds               */
       time_inc,          /* Time increment for next energy calculation*/
       ax,                /* Acceleration data in x                    */
       ay,                /* Acceleration data in y                    */
       az,                /* Acceleration data in z                    */
       sex,               /* male = 1, female = 2                      */
       age,               /* Age in years                              */
       weight,            /* Weight in kg                              */
       height,            /* Height in cm                              */
       ref_time_length,   /* Time lengths for the references           */
       reference_act_ids, /* Activity IDs for the references           */
       num_references,    /* Number of references                      */
       references_x,      /* References                                */
       references_y,      /* References                                */
      &energy,            /* Energy                                    */
       correlations,      /* Correlations for each of the references   */
      &power,             /* Signal power                              */
      &activity,          /* Determined activity                       */
       workspace);        /* pre-allocated buffer space. Size = TBD    */

   return 0;
}
