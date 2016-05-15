#include "sensor.h"
#include <stdlib.h>

int main()
{

   const float sampling_freq    = 100.0f;
   const float data_time_length = 4.0f;
   const float total_data_time_length = 30.0f;
   float *ax = (float*)malloc( 8000 );
   float *ay = (float*)malloc( 8000 );
   float *az = (float*)malloc( 8000 );
   const float ref_time_length = 1.5f;
   float *reference_x = (float*)malloc( (int)(ref_time_length * sampling_freq) );
   float *reference_y = (float*)malloc( (int)(ref_time_length * sampling_freq) );
   const int num_samples = 40;
   void  *workspace = malloc( 20000 );

training_main(
         sampling_freq,          /* Sampling frequency                          */
         data_time_length,       /* data time length in seconds                 */
         total_data_time_length, /* total time length of the incoming data      */
         ax,                     /* Acceleration data in x                      */
         ay,                     /* Acceleration data in x                      */
         az,                     /* Acceleration data in x                      */
         ref_time_length,        /* Time length for the reference               */
         reference_x,            /* Reference x                                 */
         reference_y,            /* Reference y                                 */
         num_samples,            /* Number of samples to test for reference     */
         workspace);

   free( ax );
   free( ay );
   free( az );
   free( reference_x );
   free( reference_y );
   free( workspace );

   return 0;
}
