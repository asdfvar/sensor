/* Routine to compute the eigenvalues and eigenvectors of a real symmetric 3x3 matrix.
 * The algorithm for this routine can be generalized to any NxN matrix.
 *
 * The algorithm used here for computing the eigenvalues and eigenvectos uses the
 * QR decomposition of the matrix and then iteratively repeats this process as follows:
 *
 * The input matrix is copied to a temporary array A.
 * Then the Q and R decomposition is computed from A (A = QR).
 * A new A term is computed via A := RQ.
 * Then the above 2 lines are repeated until the diagonal terms of A
 * differ from the previous iteration by some tolerance.
 * The eigenvalues are the diagonal terms of A and the
 * eigenvectors are the columns of the product of all the Q terms in succession
 * V = Q_0 * Q_1 * ... * Q_n
 */

#include <cmath>
#include <iostream>

/* Some anscillary functions are provided first */

/* Compute the matrix multiplication of the NxN matrices A and B.
 *
 * C = A * B
 *
 * Inputs:
 * A  - The matrix A
 * Bt - The transpose of matrix B
 * N  - The dimensions (NxN) of the matrices A and B
 *
 * Output:
 * C  - The result of A*B
 *
 * C can be computed in place.
 * Only supports up to 3x3.
*/

#define MAX_COUNT 100

static void matrix_mult_transpose(float *C, const float *A, const float *Bt,
                                  const int N) {

   float tmp[3];

   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         tmp[j] = 0.0;
         for (int k = 0; k < N; k++)
            tmp[j] += A[i*N + k]*Bt[j*N + k];
      }
      for (int j = 0; j < N; j++) C[i*N + j] = tmp[j];
   }

}

/* Compute the matrix multiplication of the NxN matrices A and B.
 *
 * C = A * B
 *
 * Inputs:
 * A  - The matrix A
 * Bt - The transpose of matrix B
 * N  - The dimensions (NxN) of the matrices A and B
 *
 * Output:
 * Ct - The transposed result of A*B
 *
*/

static void transpose_matrix_mult_transpose(float *Ct, const float *A, const float *Bt,
                                  const int N) {

   for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
         Ct[j*N + i] = 0.0;
         for (int k = 0; k < N; k++)
            Ct[j*N + i] += A[i*N + k]*Bt[j*N + k];
      }
   }

}

/***************************************************************************************/

/* Determine the eigenvectors of a 3x3 real symetric matrix
 * (or at least have real eigenvalues and eigenvectors)
 *
 * Input:
 * mat[3][3] - 3x3 matrix to compute the eigenvalues and eigenvectors from
 *
 * Output:
 * eigVl -  3 element array to hold the eigenvalues
 * eigVec - 3x3 element array to hold the eigenvalues in the following order:
 *               [ eigenvector 1 ]
 *               [ eigenvector 2 ]
 *               [ eigenvector 3 ]
 *
 * Note:
 * Some matrices are kept in their transpose form to take
 * advantage of any potential auto vectorization offered
 * by the compiler whenever certain operations happen in
 * contiguous memory.
 */

void eigen(const float mat[3][3], float *eigVl, float *eigVec)
{

   int i,j,k;

   float norm;
   float prod1, prod2;

  /* A will be kept in its transposed form.
   * a1, a2, and a3 will alias the vector compenents comprising A
   *
   *     [---a1---]
   * A = [---a2---]
   *     [---a3---]
   */
   float A[3][3];
   float *a1 = &A[0][0];
   float *a2 = &A[1][0];
   float *a3 = &A[2][0];

   // Copy the transpose of the input matrix into A
   for (k = 0; k < 9; k++) a1[k] = mat[k][0];
   for (k = 0; k < 9; k++) a2[k] = mat[k][1];
   for (k = 0; k < 9; k++) a3[k] = mat[k][2];

  /* Q will be kept in its transposed form.
   * Q is intended to hold the Q component of
   * the QR decomposition of A.
   * q1, q2, and q3 will alias the vector components comprising Q
   *
   *     [---q1---]
   * Q = [---q2---]
   *     [---q3---]
   */
   float Q[3][3];
   float *q1 = &Q[0][0];
   float *q2 = &Q[1][0];
   float *q3 = &Q[2][0];

  /* R is inetended to hold the R component of
   * the QR decomposition of A.
   *
   *     [    |    |    ]
   * R = [ r1 | r2 | r3 ]
   *     [    |    |    ]
   */
   float R[3][3];

  /* V is intended to hold the eigenvectors along its
   * columns. It starts out as the identity matrix and
   * will converge to the eigenvectors over enough iterations.
   *
   *     [    |    |    ]
   * V = [ v1 | v2 | v3 ]
   *     [    |    |    ]
   */
   float V[3][3];
   for (i = 0; i < 3; i++) {
      for (j = 0; j < 3; j++) {
         if (i == j) V[i][j] = 1.0;
         else V[i][j] = 0.0;
      }
   }

   // Parameters used for convergence computation
   float prev[3] = {0.0, 0.0, 0.0};
   float err;
   unsigned int count = 0;

   do {

      /* Q */

      // q1
      for (k = 0; k < 3; k++) q1[k] = a1[k];
      norm = 0.0;
      for (k = 0; k < 3; k++) norm += q1[k]*q1[k];
      norm = sqrtf(norm);
      for (k = 0; k < 3; k++) q1[k] /= norm;

      // q2
      prod1 = 0.0;
      for (k = 0; k < 3; k++) prod1 += q1[k]*a2[k];
      for (k = 0; k < 3; k++) q2[k] = a2[k] - prod1 * q1[k];
      norm = 0.0;
      for (k = 0; k < 3; k++) norm += q2[k]*q2[k];
      norm = sqrtf(norm);
      for (k = 0; k < 3; k++) q2[k] /= norm;

      // q3
      prod1 = prod2 = 0.0;
      for (k = 0; k < 3; k++) prod1 += q1[k]*a3[k];
      for (k = 0; k < 3; k++) prod2 += q2[k]*a3[k];
      for (k = 0; k < 3; k++) q3[k] = a3[k] - prod1 * q1[k] - prod2 * q2[k];
      norm = 0.0;
      for (k = 0; k < 3; k++) norm += q3[k]*q3[k];
      norm = sqrtf(norm);
      for (k = 0; k < 3; k++) q3[k] /= norm;

      /* R */

      // r1
      R[0][0] = 0.0;
      for (k = 0; k < 3; k++) R[0][0] += q1[k]*a1[k];
      R[1][0] = 0.0;
      R[2][0] = 0.0;

      // r2
      R[0][1] = 0.0;
      for (k = 0; k < 3; k++) R[0][1] += q1[k]*a2[k];
      R[1][1] = 0.0;
      for (k = 0; k < 3; k++) R[1][1] += q2[k]*a2[k];
      R[2][1] = 0.0;

      // r3
      R[0][2] = 0.0;
      for (k = 0; k < 3; k++) R[0][2] += q1[k]*a3[k];
      R[1][2] = 0.0;
      for (k = 0; k < 3; k++) R[1][2] += q2[k]*a3[k];
      R[2][2] = 0.0;
      for (k = 0; k < 3; k++) R[2][2] += q3[k]*a3[k];

      // V_{k+1} := V_k*Q
      matrix_mult_transpose(&V[0][0], &V[0][0], &Q[0][0], 3);
      // A_{k+1} = R*Q. Where A_k = Q*R.
      transpose_matrix_mult_transpose(&A[0][0], &R[0][0], &Q[0][0], 3);

      // Extract the eigenvalues
      for (k = 0; k < 3; k++) eigVl[k] = A[k][k];

      // Compute the difference between this set of eigenvvalues from the previous
      err = 0.0;
      for (k = 0; k < 3; k++) err += (prev[k] - eigVl[k]) * (prev[k] - eigVl[k]);
      for (k = 0; k < 3; k++) prev[k] = eigVl[k];

      count++;

   } while (err > 0.000001 && count < MAX_COUNT);

   if ( count >= MAX_COUNT )
      std::cout << "Warning: Eigenvalues and eigenvectors may not have converged" << std::endl;

  /* The eigenvectors are transposed for output
   *
   *          [---v1---]
   * eigVec = [---v2---] = transpose(V)
   *          [---v3---]
   */
   for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
         eigVec[i*3 + j] = V[j][i];

}
