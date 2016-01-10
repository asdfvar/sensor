#include "local_trig.h"
#include <math.h>
#include <stdio.h>

#define PI 3.14159265358979323f

int main()
{

   float x = 11.0f/8.0f * PI;

   float y   = sinf(x);
   float y_l = local_sin(x);

   printf("      sin(%f) = %.16f\nlocal sin(%f) = %.16f\n", x,y,x,y_l);

   y   = cosf(x);
   y_l = local_cos(x);

   printf("      cos(%f) = %.16f\nlocal cos(%f) = %.16f\n", x,y,x,y_l);

   return 0;
}
