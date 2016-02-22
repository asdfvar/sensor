#ifndef QMATH_H
#define QMATH_H

#ifndef PC

  /*
  ** For micro-controller compiled code
  */

  #include "QmathLib.h"

  #define BYTES_PER_ELMNT 2

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
  #define QMATH_Q1sqrt(A)      _Q1sqrt(A)
  #define QMATH_Q2sqrt(A)      _Q2sqrt(A)
  #define QMATH_Q3sqrt(A)      _Q3sqrt(A)
  #define QMATH_Q4sqrt(A)      _Q4sqrt(A)
  #define QMATH_Q5sqrt(A)      _Q5sqrt(A)
  #define QMATH_Q6sqrt(A)      _Q6sqrt(A)
  #define QMATH_Q7sqrt(A)      _Q7sqrt(A)
  #define QMATH_Q8sqrt(A)      _Q8sqrt(A)
  #define QMATH_Q9sqrt(A)      _Q9sqrt(A)
  #define QMATH_Q10sqrt(A)     _Q10sqrt(A)
  #define QMATH_Q11sqrt(A)     _Q11sqrt(A)
  #define QMATH_Q12sqrt(A)     _Q12sqrt(A)
  #define QMATH_Q13sqrt(A)     _Q13sqrt(A)
  #define QMATH_Q14sqrt(A)     _Q14sqrt(A)
  #define QMATH_Q15sqrt(A)     _Q15sqrt(A)

  // division
  #define QMATH_Q1div(A, B)    _Q1div(A, B)
  #define QMATH_Q2div(A, B)    _Q2div(A, B)
  #define QMATH_Q3div(A, B)    _Q3div(A, B)
  #define QMATH_Q4div(A, B)    _Q4div(A, B)
  #define QMATH_Q5div(A, B)    _Q5div(A, B)
  #define QMATH_Q6div(A, B)    _Q6div(A, B)
  #define QMATH_Q7div(A, B)    _Q7div(A, B)
  #define QMATH_Q8div(A, B)    _Q8div(A, B)
  #define QMATH_Q9div(A, B)    _Q9div(A, B)
  #define QMATH_Q10div(A, B)   _Q10div(A, B)
  #define QMATH_Q11div(A, B)   _Q11div(A, B)
  #define QMATH_Q12div(A, B)   _Q12div(A, B)
  #define QMATH_Q13div(A, B)   _Q13div(A, B)
  #define QMATH_Q14div(A, B)   _Q14div(A, B)
  #define QMATH_Q15div(A, B)   _Q15div(A, B)

#else ///////////////////////////////////////

  /*
  ** For PC compiled code
  */

  #include <math.h>

  #define BYTES_PER_ELMNT 4

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

  // square root
  #define QMATH_Q1sqrt(A)      sqrtf(A)
  #define QMATH_Q2sqrt(A)      sqrtf(A)
  #define QMATH_Q3sqrt(A)      sqrtf(A)
  #define QMATH_Q4sqrt(A)      sqrtf(A)
  #define QMATH_Q5sqrt(A)      sqrtf(A)
  #define QMATH_Q6sqrt(A)      sqrtf(A)
  #define QMATH_Q7sqrt(A)      sqrtf(A)
  #define QMATH_Q8sqrt(A)      sqrtf(A)
  #define QMATH_Q9sqrt(A)      sqrtf(A)
  #define QMATH_Q11sqrt(A)     sqrtf(A)
  #define QMATH_Q12sqrt(A)     sqrtf(A)
  #define QMATH_Q13sqrt(A)     sqrtf(A)
  #define QMATH_Q14sqrt(A)     sqrtf(A)
  #define QMATH_Q15sqrt(A)     sqrtf(A)
  #define QMATH_Q16sqrt(A)     sqrtf(A)

  // division
  #define QMATH_Q1div(A, B)    (A / B)
  #define QMATH_Q2div(A, B)    (A / B)
  #define QMATH_Q3div(A, B)    (A / B)
  #define QMATH_Q4div(A, B)    (A / B)
  #define QMATH_Q5div(A, B)    (A / B)
  #define QMATH_Q6div(A, B)    (A / B)
  #define QMATH_Q7div(A, B)    (A / B)
  #define QMATH_Q8div(A, B)    (A / B)
  #define QMATH_Q9div(A, B)    (A / B)
  #define QMATH_Q10div(A, B)   (A / B)
  #define QMATH_Q11div(A, B)   (A / B)
  #define QMATH_Q12div(A, B)   (A / B)
  #define QMATH_Q13div(A, B)   (A / B)
  #define QMATH_Q14div(A, B)   (A / B)
  #define QMATH_Q15div(A, B)   (A / B)

#endif

#endif
