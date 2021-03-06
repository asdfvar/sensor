#ifndef SENSOR_MAIN_H
#define SENSOR_MAIN_H

void prep_ref(
 /* [IO] */ float       *ref_ax,
 /* [IO] */ float       *ref_ay,
 /* [IO] */ float       *ref_az,
 /* [I ] */ const float  ref_time_length,
 /* [I ] */ const float  data_time_length,
 /* [I ] */ float        sampling_freq,
 /* [I ] */ const int    downsamp_fract,
 /* [**] */ void        *workspace);

void sensor_main(
 /*[I ]*/ const float sampling_freq,     /* Sampling frequency                        */
 /*[I ]*/ const float data_time_length,  /* Data time length in seconds               */
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
 /*[I ]*/ float      *references_x,      /* Array of references in x                  */
 /*[I ]*/ float      *references_y,      /* Array of references in y                  */
 /*[ O]*/ float      *energy,            /* Energy                                    */
 /*[ O]*/ float      *correlations,      /* Correlations for each of the references   */
 /*[ O]*/ float      *power,             /* Signal power                              */
 /*[ O]*/ int        *activity,          /* Determined activity                       */
 /*[ O]*/ void       *workspace);        /* pre-allocated buffer space. Size = TBD    */

void training_main(
 /*[I ]*/ const float  sampling_freq,          /* Sampling frequency                          */
 /*[I ]*/ const float  data_time_length,       /* data time length in seconds                 */
 /*[I ]*/ const float  total_data_time_length, /* total time length of the incoming data      */
 /*[I ]*/ const float *ax,                     /* Acceleration data in x                      */
 /*[I ]*/ const float *ay,                     /* Acceleration data in x                      */
 /*[I ]*/ const float *az,                     /* Acceleration data in x                      */
 /*[I ]*/ const float  ref_time_length,        /* Time length for the reference               */
 /*[ O]*/ float       *reference_x,            /* Reference x                                 */
 /*[ O]*/ float       *reference_y,            /* Reference y                                 */
 /*[ O]*/ float       *reference_z,            /* Reference z                                 */
 /*[I ]*/ const int    num_samples,            /* Number of samples to test for reference     */
 /*[**]*/ void        *workspace);

#endif
