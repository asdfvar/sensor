/******************************************************
 * Feed forward
 *
 * Return a pointer to the output of the network given
 * the provided input.
 ******************************************************/

#include "ann.h"

float *ann::forward(float *inp){
   
   int i,j;
   float *xp, *wp, *vp;
   float *output;
   
   // Set the first layer values to the input values
   for (i = 0; i < LayerSizes[0]; i++)
      x[i] = inp[i];
   
   // Define the current positions
   xp = x; wp = w; vp = v;
   
   for (i = 0; i < N-1; i++){
   
      // Apply the weights to the next layer
      mult(xp + LayerSizes[i], wp, xp, LayerSizes[i+1], LayerSizes[i]);
      
      // Advance to the next layer
      xp += LayerSizes[i];
      
      // Advance the weights to the next layer
      wp += LayerSizes[i] * LayerSizes[i+1];
   
      // Apply the bias weights to the current layer
      for (j = 0; j < LayerSizes[i+1]; j++)
         xp[j] += bias * vp[j];
      
      // Advance the bias weights to the next layer
      vp += LayerSizes[i+1];
      
      // Apply the activation function to the current layer
      for (j = 0; j < LayerSizes[i+1]; j++)
         xp[j] = g(xp[j], beta);
    
   }
   
   output = xp;
   
   return output;
}
