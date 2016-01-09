#include "local_trig.h"
#include <stdio.h>

// https://sourceware.org/git/?p=glibc.git;a=blob;f=sysdeps/ieee754/dbl-64/s_sin.c;hb=HEAD#l281

inline float local_sin(float x)
{

   float result = 0.0f;

   int k;
   float p;
   float coef = x;
   for (k = 0, p = 1; k < 100; k++, p += 2.0f)
   {
      result += coef;

      coef *= - x * x / ((p + 1.0f) * (p + 2.0f));
   }

   return result;

}
