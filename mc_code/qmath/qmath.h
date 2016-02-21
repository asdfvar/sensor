#ifndef QMATH_H
#define QMATH_H

#ifndef PC

  /*
  ** For micro-controller compiled code
  */

  #include "iqmath.h"

  // type declaration
  #define QMATH_q1     _q1
  #define QMATH_q2     _q2
  #define QMATH_q3     _q3
  #define QMATH_q4     _q4
  #define QMATH_q5     _q5
  #define QMATH_q6     _q6
  #define QMATH_q7     _q7
  #define QMATH_q8     _q8
  #define QMATH_q9     _q9
  #define QMATH_q10    _q10
  #define QMATH_q11    _q11
  #define QMATH_q12    _q12
  #define QMATH_q13    _q13
  #define QMATH_q14    _q14
  #define QMATH_q15    _q15

  // type casting
  #define QMATH_Q1(A)  _Q1(A)
  #define QMATH_Q2(A)  _Q2(A)
  #define QMATH_Q3(A)  _Q3(A)
  #define QMATH_Q4(A)  _Q4(A)
  #define QMATH_Q5(A)  _Q5(A)
  #define QMATH_Q6(A)  _Q6(A)
  #define QMATH_Q7(A)  _Q7(A)
  #define QMATH_Q8(A)  _Q8(A)
  #define QMATH_Q9(A)  _Q9(A)
  #define QMATH_Q10(A) _Q10(A)
  #define QMATH_Q11(A) _Q11(A)
  #define QMATH_Q12(A) _Q12(A)
  #define QMATH_Q13(A) _Q13(A)
  #define QMATH_Q14(A) _Q14(A)
  #define QMATH_Q15(A) _Q15(A)

  // multiplication
  #define QMATH_Q1mpy(A, B)    _Q1mpy(A, B)
  #define QMATH_Q2mpy(A, B)    _Q2mpy(A, B)
  #define QMATH_Q3mpy(A, B)    _Q3mpy(A, B)
  #define QMATH_Q4mpy(A, B)    _Q4mpy(A, B)
  #define QMATH_Q5mpy(A, B)    _Q5mpy(A, B)
  #define QMATH_Q6mpy(A, B)    _Q6mpy(A, B)
  #define QMATH_Q7mpy(A, B)    _Q7mpy(A, B)
  #define QMATH_Q8mpy(A, B)    _Q8mpy(A, B)
  #define QMATH_Q9mpy(A, B)    _Q9mpy(A, B)
  #define QMATH_Q10mpy(A, B)   _Q10mpy(A, B)
  #define QMATH_Q11mpy(A, B)   _Q11mpy(A, B)
  #define QMATH_Q12mpy(A, B)   _Q12mpy(A, B)
  #define QMATH_Q13mpy(A, B)   _Q13mpy(A, B)
  #define QMATH_Q14mpy(A, B)   _Q14mpy(A, B)

  // square root
  #define QMATH_Q9sqrt(A)      _Q(X)sqrt(A)

  // division
  #define QMATH_Q9div(A, B)    _Q(X)div(A, B)

#else

  /*
  ** For PC compiled code
  */

  #include <math.h>

  #define QMATH_q1     float
  #define QMATH_q2     float
  #define QMATH_q3     float
  #define QMATH_q4     float
  #define QMATH_q5     float
  #define QMATH_q6     float
  #define QMATH_q7     float
  #define QMATH_q8     float
  #define QMATH_q9     float
  #define QMATH_q10    float
  #define QMATH_q11    float
  #define QMATH_q12    float
  #define QMATH_q13    float
  #define QMATH_q14    float
  #define QMATH_q15    float

  #define QMATH_Q1(A)    (A)
  #define QMATH_Q2(A)    (A)
  #define QMATH_Q3(A)    (A)
  #define QMATH_Q4(A)    (A)
  #define QMATH_Q5(A)    (A)
  #define QMATH_Q6(A)    (A)
  #define QMATH_Q7(A)    (A)
  #define QMATH_Q8(A)    (A)
  #define QMATH_Q9(A)    (A)
  #define QMATH_Q10(A)   (A)
  #define QMATH_Q11(A)   (A)
  #define QMATH_Q12(A)   (A)
  #define QMATH_Q13(A)   (A)
  #define QMATH_Q14(A)   (A)
  #define QMATH_Q15(A)   (A)

  // multiplication
  #define QMATH_Q1mpy(A, B)    (A * B)
  #define QMATH_Q2mpy(A, B)    (A * B)
  #define QMATH_Q3mpy(A, B)    (A * B)
  #define QMATH_Q4mpy(A, B)    (A * B)
  #define QMATH_Q5mpy(A, B)    (A * B)
  #define QMATH_Q6mpy(A, B)    (A * B)
  #define QMATH_Q7mpy(A, B)    (A * B)
  #define QMATH_Q8mpy(A, B)    (A * B)
  #define QMATH_Q9mpy(A, B)    (A * B)
  #define QMATH_Q10mpy(A, B)   (A * B)
  #define QMATH_Q11mpy(A, B)   (A * B)
  #define QMATH_Q12mpy(A, B)   (A * B)
  #define QMATH_Q13mpy(A, B)   (A * B)
  #define QMATH_Q14mpy(A, B)   (A * B)
  #define QMATH_Q15mpy(A, B)   (A * B)

  #define QMATH_Q9sqrt(A)      sqrtf(A)

  #define QMATH_Q9div(A, B)    (A / B)

#endif

#endif
