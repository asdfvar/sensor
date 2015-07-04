#include "filter.h"

namespace util {
/*
 * Function NAME: filter
 *
 * Applies a tent filter to the data
 *
 * [IO] data
 * [I ] points     - width of the tent filter
 * [I ] mem_buffer - buffer space object must have at least
 *                   2 * N words of float data available
 */

void filter (float *data,
                   int    points,
                   int    N,
                   MEMORY mem_buffer)
{

   float *z    = mem_buffer.allocate_float( N );
   float *orig = mem_buffer.allocate_float( N );

   int    half = points / 2;
   int    den_half = half * (half + 2) + 1;
   float scale = 1.0f / (float)den_half;

   for (int k = 0; k < N; k++) orig[k] = data[k];
   for (int k = 0; k < N; k++) z[k]    = 0.0f;

   for (int p = 0; p < half; p++)
   {

      int offset = half - p;
      for (int k = 0; k < N; k++) z[k] += orig[k];
      for (int k = 0; k < N - half + p; k++) data[k         ] += z[k + offset];
      for (int k = 0; k < N - half + p; k++) data[k + offset] += z[k         ];

   }

   for (int k = 0; k < N; k++) data[k] += z[k];

   /*
   ** Normalize the interior points of the resulting smoothed data
   */

   for (int k = half; k < N - half; k++)
   {
      data[k] *= scale;
   }

   /*
   ** Normalize the end points of the resulting smoothed data
   */

   float norm;
   for (int k = 0; k < half; k++)
   {
      norm = (float)(den_half - ((half - k)*(half - k+1)/2));

      data[k] /= norm;
   }

   for (int k = 0, p = N; p > N - half; p--, k++)
   {
      norm = (float)(den_half - ((half - k)*(half - k+1)/2));

      data[p-1] /= norm;
   }
}

}
