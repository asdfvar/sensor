#include "filter.h"

/*
 * Function NAME: filter
 *
 * Applies a tent filter to the data
 *
 * [IO] data
 * [I ] points     - width of the tent filter
 * [I ] workspace - buffer space object must have at least
 *                   2 * N words of float data available
 */

void filter (float *data,
             int    points,
             int    N,
             float *workspace)
{

   int k,p;

   float *z    = workspace;
          workspace += N;
   float *orig = workspace;
          workspace += N;

   int    half = points / 2;
   int    den_half = half * (half + 2) + 1;
   float scale = 1.0f / (float)den_half;

   for (k = 0; k < N; k++) orig[k] = data[k];
   for (k = 0; k < N; k++) z[k]    = 0.0f;

   for (p = 0; p < half; p++)
   {
      int offset = half - p;
      for (k = 0; k < N; k++) z[k] += orig[k];
      for (k = 0; k < N - half + p; k++) data[k         ] += z[k + offset];
      for (k = 0; k < N - half + p; k++) data[k + offset] += z[k         ];
   }

   for (k = 0; k < N; k++) data[k] += z[k];

   /*
   ** Normalize the interior points of the resulting smoothed data
   */

   for (k = half; k < N - half; k++)
   {
      data[k] *= scale;
   }

   /*
   ** Normalize the end points of the resulting smoothed data
   */

   float norm;
   for (k = 0; k < half; k++)
   {
      norm = (float)(den_half - ((half - k)*(half - k+1)/2));
      data[k] /= norm;
   }

   for (k = 0, p = N; p > N - half; p--, k++)
   {
      norm = (float)(den_half - ((half - k)*(half - k+1)/2));
      data[p-1] /= norm;
   }
}
