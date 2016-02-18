/* Routine to compute the eigenvalues and eigenvectors of a real symmetric 3x3 matrix.
** The algorithm for this routine can be generalized to any NxN matrix.
**
** The algorithm used here for computing the eigenvalues and eigenvectos uses the
** QR decomposition of the matrix and then iteratively repeats this process as follows:
**
** The input matrix is copied to a temporary array A.
** Then the Q and R decomposition is computed from A (A = QR).
** A new A term is computed via A := RQ.
** Then the above 2 lines are repeated until a desired convergence is aquired.
** The eigenvalues are the diagonal terms of A and the
** eigenvectors are the columns of the product of all the Q terms in succession
** V = Q_0 * Q_1 * ... * Q_n
*/

#include <math.h>
#include <stdio.h>
#include "eigen.h"

/*
** Function NAME: matrix_mult
** 
** Compute the matrix multiplication of the NxN matrices A and B.
**
** C = A * B
**
** Inputs:
** A  - The matrix A
** B  - The matrix B
** N  - The dimensions (NxN) of the matrices A and B
**
** Output:
** C  - The result of A*B
**
** C can be computed in place (A = C).
** Only supports up to 3x3.
*/
static void matrix_mult(float       *__restrict__ C,
                        const float *__restrict__ A,
                        const float *__restrict__ B,
                        const int                 N)
{

   float tmp[3];
   int i,j,k;

   for (i = 0; i < N; i++)
   {
      for (j = 0; j < N; j++)
      {
         tmp[j] = 0.0f;
         for (k = 0; k < N; k++)
            tmp[j] += A[i*N + k]*B[k*N + j];
      }
      for (j = 0; j < N; j++) C[i*N + j] = tmp[j];
   }

}

/*
** Function NAME: outer_product
** 
** Compute the outer product of two vectors
**
** C = a * b'
**
** Inputs:
** a  - vector a of length M
** b  - vector b of length N
**
** Output:
** C  - the result of size MxN of a * b'
**
*/
static void outer_product(float       *__restrict__ C,
                          const float *__restrict__ a,
                          const int                 M,
                          const float *__restrict__ b,
                          const int                 N)
{
   int i,j;

   for (i = 0; i < M; i++)
      for (j = 0; j < N; j++)
         C[i*N + j] = a[i] * b[j];
}

/*
** Function NAME: eigen
**
** Determine the eigenvectors of a 3x3 real symetric matrix
** (or at least have real eigenvalues and eigenvectors)
**
** Input:
** mat[3][3] - 3x3 matrix to compute the eigenvalues and eigenvectors from
**
** Output:
** eigVl -  3 element array to hold the eigenvalues
** eigVec - 3x3 element array to hold the eigenvalues in the following order:
**               [ eigenvector 1 ]
**               [ eigenvector 2 ]
**               [ eigenvector 3 ]
**
** Note:
** Some matrices are kept in their transpose form to take
** advantage of any potential auto vectorization offered
** by the compiler whenever certain operations happen in
** contiguous memory.
**
** On exit, this routine returns the number of iterations
** performed until it converged or reached its maximum number
** of iterations.
*/

int eigen(float mat[3][3],
          float *__restrict__ eigVl,
          float *__restrict__ eigVec)
{

   int i,j,k;

   float norm;
   float prod1, prod2;

  /* A will be kept in its transposed form.
  **
  **     [---a1---]
  ** A = [---a2---]
  **     [---a3---]
  */
   float A[3][3];

  /* Q will be kept in its transposed form.
  ** Q is intended to hold the Q component of
  ** the QR decomposition of A.
  ** q1, q2, and q3 will alias the vector components comprising Q
  **
  **     [---q1---]
  ** Q = [---q2---]
  **     [---q3---]
  */
   float Q[3][3];
   float *q1 = &Q[0][0];
   float *q2 = &Q[1][0];
   float *q3 = &Q[2][0];

  /* R is inetended to hold the R component of
  ** the QR decomposition of A.
  **
  **     [    |    |    ]
  ** R = [ r1 | r2 | r3 ]
  **     [    |    |    ]
  */
   float R[3][3];

  /* V is intended to hold the eigenvectors along its
  ** columns. It starts out as the identity matrix and
  ** will converge to the eigenvectors over enough iterations.
  **
  **     [    |    |    ]
  ** V = [ v1 | v2 | v3 ]
  **     [    |    |    ]
  */
   float V[3][3];
   float *v = &V[0][0];

   for (k = 0; k < 9; k++) v[k]    = 0.0f;
   for (k = 0; k < 3; k++) V[k][k] = 1.0f;

   // Parameters used for convergence computation
   unsigned int count = 0;

   float R1, R2, R3;
   float maxR;

   // A = mat
   for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
         A[i][j] = mat[i][j];

   float *a = &A[0][0];
   float P[3][3];
   float *p = &P[0][0];

   float *r = &R[0][0];
   float U[3][3];
   float *u = &U[0][0];
   float T[3][3];
   float *t = &T[0][0];

   float x[3];
   float uv[3];
   int column;

   // V = I
   for (k = 0; k < 9; k++) v[k]    = 0.0f;
   for (k = 0; k < 3; k++) V[k][k] = 1.0f;

   do
   {
      // R = A
      for (i = 0; i < 3; i++)
         for (j = 0; j < 3; j++)
            R[i][j] = A[i][j];

      for (k = 0; k < 9; k++) p[k]    = 0.0f;
      for (k = 0; k < 3; k++) P[k][k] = 1.0f;

      for (column = 0; column < 2; column++)
      {
         // x = column of R
         for (k = 0; k < 3; k++)      x[k] = R[k][column];
         for (k = 0; k < column; k++) x[k] = 0.0f;

         // uv = x - |x|*e_column
         norm = 0.0f;
         for (k = 0; k < 3; k++) norm += x[k]*x[k];
         norm = sqrtf(norm);
         for (k = 0; k < 3; k++) uv[k]  = x[k]; uv[column] -= norm;

         // uv = unit vector(uv)
         norm = 0.0f;
         for (k = 0; k < 3; k++) norm += uv[k]*uv[k];
         norm = sqrtf(norm);
         if (norm > 0.000001f)
         {
            for (k = 0; k < 3; k++) uv[k] /= norm;
         }
         else
         {
            for (k = 0; k < 3; k++) uv[k] = 0.0f;
         }

         // U = I - 2*uv*uv'
         outer_product( &U[0][0], uv, 3, uv, 3);
         for (k = 0; k < 9; k++) u[k]    = -2.0f * u[k];
         for (k = 0; k < 3; k++) U[k][k] =  1.0f + U[k][k];

         // R = U * R
         matrix_mult( t, u, r, 3);
         for (k = 0; k < 9; k++) r[k] = t[k];

         // P = P * U
         matrix_mult( p, p, u, 3);

      }

      // A = R * P
      matrix_mult( a, r, p, 3);

      // V = V * P
      matrix_mult( v, v, p, 3);

      // Extract the eigenvalues
      for (k = 0; k < 3; k++) eigVl[k] = A[k][k];

      // Gershgorin circle theorem is used as the method of convergence
      R1  = ABS(A[0][1]);
      R1 += ABS(A[0][2]);
      R2  = ABS(A[1][0]);
      R2 += ABS(A[1][2]);
      R3  = ABS(A[2][0]);
      R3 += ABS(A[2][1]);
      maxR = (R1 > R2) ? R1 : R2;
      maxR = (maxR > R3) ? maxR : R3;

      count++;

   } while (maxR > MIN_ERR && count < MAX_COUNT);

  /*
   *          [---v1---]
   * eigVec = [---v2---]
   *          [---v3---]
   */
   for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
         eigVec[i*3 + j] = V[j][i];

   return count;

}
