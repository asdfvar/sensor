#ifndef PREPROC_H
#define PREPROC_H

#include "fileio.h"

int preproc(
     float *ax,             /* Acceleration data in x         */
     float *ay,             /* Acceleration data in y         */
     float *az,             /* Acceleration data in z         */
     float *power,          /* Resulting power of the signal  */
     fio::parameters*,
     const int   N);        /* Number of sample points        */

#endif
