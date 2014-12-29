#ifndef PREPROC_H
#define PREPROC_H

int preproc(
     float *ax,             /* Acceleration data in x         */
     float *ay,             /* Acceleration data in y         */
     float *az,             /* Acceleration data in z         */
     float *power,          /* Resulting power of the signal  */
     const float dt,        /* Delta time comstant            */
     const float window,    /* Time window of the data        */
     const float samp_freq, /* Sampling frequency of the data */
     const int   N);        /* Number of sample points        */

#endif
