/* This routine pre-processes the data to prepare it for use in the activity
** classification routine.
**
** The x,y,z directions of acceleration are supplied on input. On output,
** the x,y,z directions will represent the acceleration data that has been
** rotated so that the primary direction of acceleration is in x, the secondary
** direction of acceleration is in y, and the third direction is in z. This
** process will be known as the dimensionality reduction of the data.
**
** The dimensionality reduction is acheived by computing the eigenvectors of
** the covariance matrix of the data. Because this matrix is a real-symmetric
** matrix, its eigenvectors are real and orthogonal to each other. The data
** is then projected onto these vectors to form a new basis to represent the data.
** This new set of basis vectors happen to lie in the directions where the
** variance in the data is the greatest. Because the direction of motion falls
** primarily within a 2-D plan, the third dimension can be disregarded for
** further processing.
**/

#include "eigen.h"
#include "filter.h"
#include <stdio.h>

/*
 * Function NAME: preproc
 */
void preproc(
     float *__restrict__ ax,             /* Acceleration data in x          */
     float *__restrict__ ay,             /* Acceleration data in y          */
     float *__restrict__ az,             /* Acceleration data in z          */
     float *__restrict__ power,          /* Resulting power of the signal   */
     float dt,                           /* Delta time increment            */
     float time_window,                  /* Time window                     */
     float *workspace,
     const int   N)                      /* Number of sample points         */
{

   int i,j,k;
   float cov_mat[3][3]; // Covariance matrix

   /*
   ** Demean the data
   */
   float ave;
   for (k = 0, ave = 0.0; k < N; k++) ave += ax[k];
   ave /= (float) N;
   for (k = 0; k < N; k++) ax[k] -= ave;

   for (k = 0, ave = 0.0; k < N; k++) ave += ay[k];
   ave /= (float) N;
   for (k = 0; k < N; k++) ay[k] -= ave;

   for (k = 0, ave = 0.0; k < N; k++) ave += az[k];
   ave /= (float) N;
   for (k = 0; k < N; k++) az[k] -= ave;

   /*
   ** Compute the power of the signal
   */
   if (power) {
      *power = 0.0;
      for (k = 0; k < N; k++) {
         *power += ax[k] * ax[k];
         *power += ay[k] * ay[k];
         *power += az[k] * az[k];
      }
      *power *= dt;
      *power /= time_window;
   }

   /*
   ** Build the covariance matrix
   */
   for (i = 0; i < 3; i++)
      for (j = 0; j < 3; j++)
         cov_mat[i][j] = 0.0;

   for (k = 0; k < N; k++) {
      cov_mat[0][0] += ax[k] * ax[k];
      cov_mat[0][1] += ax[k] * ay[k];
      cov_mat[0][2] += ax[k] * az[k];
      cov_mat[1][1] += ay[k] * ay[k];
      cov_mat[1][2] += ay[k] * az[k];
      cov_mat[2][2] += az[k] * az[k];
   }

   cov_mat[1][0] = cov_mat[0][1];
   cov_mat[2][0] = cov_mat[0][2];
   cov_mat[2][1] = cov_mat[1][2];

   float eigVal[3];
   float eigVec[3][3];

   eigen(cov_mat, eigVal, &eigVec[0][0]);

   float tmp;

   /*
   ** Re-order the eigenvalues in descending order along
   ** with their associated eigenvectors
   */
   for (i = 0; i < 2; i++) {
      for (j = 0; j < 2; j++) {
         if (eigVal[j] < eigVal[j+1]) {
            tmp = eigVal[j];
            eigVal[j] = eigVal[j+1];
            eigVal[j+1] = tmp;

            for (k = 0; k < 3; k++){
               tmp = eigVec[j][k];
               eigVec[j][k] = eigVec[j+1][k];
               eigVec[j+1][k] = tmp;
            }
         }
      }
   }

   /*
   ** Re-orient the axes in the direction of motion.
   ** The z-direction will be assumed to be near zero.
   */
   float *eigVec_1 = &eigVec[0][0];
   float *eigVec_2 = &eigVec[1][0];

   float x, y;

   for (k = 0; k < N; k++) {
      x = ax[k]*eigVec_1[0] + ay[k]*eigVec_1[1] + az[k]*eigVec_1[2];
      y = ax[k]*eigVec_2[0] + ay[k]*eigVec_2[1] + az[k]*eigVec_2[2];
      ax[k] = x;
      ay[k] = y;
      az[k] = 0.0f;
   }

   int points = (int)(0.05f / dt);
   if (points % 2 == 0) points++;

   filter (ax,
           points,
           N,
           workspace);

   filter (ay,
           points,
           N,
           workspace);

   return;
}
