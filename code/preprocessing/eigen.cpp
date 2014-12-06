/* Determine the eigenvalues of a 3x3 real symmetric matrix */
void eigen_val(const float mat[3][3], float *eig)
{

/*
// Octave/Matlab code from http://en.wikipedia.org/wiki/Eigenvalue_algorithm
% Given a real symmetric 3x3 matrix A, compute the eigenvalues
 
p1 = A(1,2)^2 + A(1,3)^2 + A(2,3)^2
if (p1 == 0) 
   % A is diagonal.
   eig1 = A(1,1)
   eig2 = A(2,2)
   eig3 = A(3,3)
else
   q = trace(A)/3
   p2 = (A(1,1) - q)^2 + (A(2,2) - q)^2 + (A(3,3) - q)^2 + 2 * p1
   p = sqrt(p2 / 6)
   B = (1 / p) * (A - q * I)       % I is the identity matrix
   r = det(B) / 2
 
   % In exact arithmetic for a symmetric matrix  -1 <= r <= 1
   % but computation error can leave it slightly outside this range.
   if (r <= -1) 
      phi = pi / 3
   elseif (r >= 1)
      phi = 0
   else
      phi = acos(r) / 3
   end
 
   % the eigenvalues satisfy eig3 <= eig2 <= eig1
   eig1 = q + 2 * p * cos(phi)
   eig3 = q + 2 * p * cos(phi + (2*pi/3))
   eig2 = 3 * q - eig1 - eig3     % since trace(A) = eig1 + eig2 + eig3
end
*/

// delete this
for (int k = 0; k < 3; k++) eig[k] = mat[k][0] + mat[k][1] + mat[k][2];

}

/***************************************************************************************/

/* Determine the eigen vectors of the 3x3 real symmetric matrix given its aigen values */
void eigen_vec(const float mat[3][3], const float eig[3], float *eigVec)
{

   int i,j,k;

   // delete this
   for (k = 0, i = 0; i < 3; i++)
      for (j = 0; j < 3; j++, k++)
         eigVec[k] = mat[i][j] * eig[j];

}

/***************************************************************************************/

/* Determine the eigen vectors of the 3x3 real symmetric matrix */
void eigen_vec(const float mat[3][3], float *eigVec)
{

   float eig[3];

   eigen_val(mat, eig);
   eigen_vec(mat, eig, eigVec);

}
