void apply_filter (float *data,
                   int    fill,
                   int    N)
{

   float hold[3] = {0.0f, 0.0f, 0.0f};
   float hist[3];

   hist[0] = data[0];
   hist[1] = data[1];
   hist[2] = data[2];

   data[0] = 0.6666666666f * hist[0] + 0.3333333333f * hist[1];

   float tmp;

   for (int k=1; k<N-2; k++) {
      tmp = 0.25f * hist[0] + 0.5f * hist[1] + 0.25f * hist[2];
      hist[0] = hist[1];
      hist[1] = hist[2];
      hist[2] = data[k+2];
      data[k] = tmp;
   }

   data[N-2] = 0.25f * hist[0] + 0.5f * hist[1] + 0.25f * hist[2];
   data[N-1] = 0.3333333333f * hist[1] + 0.6666666666f * hist[2];

}
