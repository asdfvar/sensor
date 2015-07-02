#include "filter.h"
/*
 * Function NAME: apply_filter
 */
void apply_filter (float *data,
                   int    points,
                   int    N,
                   MEMORY mem_buffer)
{

#if 0
   float hold[3] = {0.0f, 0.0f, 0.0f};
   float hist[3];

   hist[0] = data[0];
   hist[1] = data[1];
   hist[2] = data[2];

   const float w0 = 2.0f / 3.0f;
   const float w1 = 1.0f / 3.0f;

   data[0] = w0 * hist[0] + w1 * hist[1];

   float tmp;

   for (int k=1; k<N-2; k++) {
      tmp = 0.25f * hist[0] + 0.5f * hist[1] + 0.25f * hist[2];
      hist[0] = hist[1];
      hist[1] = hist[2];
      hist[2] = data[k+2];
      data[k] = tmp;
   }

   data[N-2] = 0.25f * hist[0] + 0.5f * hist[1] + 0.25f * hist[2];
   data[N-1] = w1 * hist[1] + w0 * hist[2];
#endif

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
   ** scale
   */

   for (int k = half; k < N - half; k++)
   {
      data[k] *= scale;
   }

   for (int k = 0; k < half; k++)
   {
      data[k] /= (float)(den_half - ((half - k)*(half - k+1)/2));
   }

   for (int k = 0, p = N; p > N - half; p--, k++)
   {
      data[p] /= (float)(den_half - ((half - k)*(half - k+1)/2));
   }
}
