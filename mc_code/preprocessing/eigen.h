#ifndef EIGEN_H
#define EIGEN_H

#define MAX_COUNT 100
#define MIN_ERR 0.001
#define MIN_NORM 0.0000001

#define ABS(A) ((A) > 0) ? (A) : -(A)

int eigen(float mat[3][3], float *eigVl, float *eigVec);

#endif
