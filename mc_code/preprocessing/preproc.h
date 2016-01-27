#ifndef PREPROC_H
#define PREPROC_H

void preproc(
     float *ax,             /* Acceleration data in x         */
     float *ay,             /* Acceleration data in y         */
     float *az,             /* Acceleration data in z         */
     float *power,          /* Resulting power of the signal  */
     float dt,
     float time_window,
     float *workspace,
     const int   N);        /* Number of sample points        */

#endif
