#include "data.h"

DATA::DATA(
   float *data_in, /* Data */
   int N_in )      /* Number of elements that make up the data */
{

   data = data_in;
   state = t_space;

}
