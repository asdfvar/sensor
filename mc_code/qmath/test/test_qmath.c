#include <stdio.h>
#include "qmath.h"

int main()
{

#ifdef PC
   printf("PC defined\n");
#else
   printf("PC not defined. Compiled for the micro-controller\n");
#endif

   QMATH_q9 x = QMATH_Q9( 7.0f );
   QMATH_q9 y = QMATH_Q9( 3.0f );
   QMATH_q9 z;

   z = QMATH_Q9mpy(x, y);

   printf("z = %f\n", QMATH_Q9toF(z));

   QMATH_q9 pi = QMATH_Q9( 3.14159265358979323f );
   QMATH_q9 diameter = QMATH_Q9( 4.0f );
   QMATH_q9 circ;

   circ = QMATH_Q9mpy(diameter, pi);

   printf("circumference = %f\n", QMATH_Q9toF(circ));

   x = QMATH_Q9( 16.0f ); // 0001 0000 0000 0000
   y = QMATH_Q9( 4.0f );  // 0000 0100 0000 0000

   z = QMATH_Q9mpy(x, y);

   printf(" 16 * 4      = %f\n", QMATH_Q9toF(z));

   x = QMATH_Q9( 15.9999f );
   y = QMATH_Q9( 4.0f );

   z = QMATH_Q9mpy(x, y);

   printf(" 15.9999 * 4 = %f\n", QMATH_Q9toF(z));

#ifdef PC
   int16_t p = 14848; // 3.625 in Q12   0000 0000 0000 0000
   int16_t q = 5120;  // 1.25 in Q12
   int16_t r;

   //r = (p >> 6) * (q >> 6);
   r = (p * q) >> 12; // 14848 * 10^-12 * 5120*10^-12 = (18560*10^-12)*10^-12
   printf("r = %d\n", r);
   printf("float(r) = %f\n", (float)(int)r * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f * 0.5f);

   int ip = 14848;
   int iq = 5120;
   int ir;

   ir = (ip * iq) >> 12;
   float fr = (float)ir;

   int k;
   for (k = 0; k < 12; k++) {
      fr *= 0.5f;
   }

   printf("fr = %f\n", fr);
#endif

   return 0;
}
