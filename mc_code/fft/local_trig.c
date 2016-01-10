#include "local_trig.h"

// https://sourceware.org/git/?p=glibc.git;a=blob;f=sysdeps/ieee754/dbl-64/s_sin.c;hb=HEAD#l281

inline float local_sin(float x)
{

   if (x > LOC_PI || x < -LOC_PI)
   {
      int q = (int)(x / LOC_PI);
      x -= (float)q * LOC_PI;

      if (q % 2 != 0) x = -x;
   }

   float result = 0.0f;

   int k;
   float p;
   float coef = x;
   for (k = 0, p = 1.0f; k < 10; k++, p += 2.0f)
   {
      result += coef;

      coef *= - x * x / ((p + 1.0f) * (p + 2.0f));
   }

   return result;
}

inline float local_cos(float x)
{
   return local_sin(x + LOC_PI_OVER_2);
}
