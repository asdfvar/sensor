/*****************************************************
 * Training
 *
 * Train the network with the provided input and output
 * data sets using the back propagation algorithm over
 * the supplied number of steps.
 *
 * There are K input and output sets.
 *
 * Defining:
 * '*'  - matrix multiplication
 * '.*' - element wise multiplication (Hadamard multiplication)
 * 'OP' - outer product
 * 
 * Backpropagation of the error starts by subtracting the output
 * of the NN 'y' from the target desired output 't'.
 * Delta = t - y                                            -> delta_{-1}
 *
 * delta_{-1} is used here to mean the end term
 *
 * Then using that "small" difference to update the next "small"
 * difference one layer back in the NN.
 * transpose(w_l) * delta_{l+1} .* (beta*x_l .* (1 - x_l))  -> delta_l
 *
 * The above is repeated until all "small" differences (delta_l) are computed.
 *
 * With the deltas computed, the weights are updated with the terms
 * delta_{l+1} OP x_l                                       -> Dw_l
 * delta_{l+1}*bias                                         -> Dv_l
 *
 * Using the above terms, the layer weights and bias weights are
 * updated
 * w_l + nu*Dw_l                                            -> w_l
 * v_l + nu*Dv_l                                            -> v_l
 * 
 * Reference (with some differences):
 * http://www.willamette.edu/~gorr/classes/cs449/backprop.html
 *****************************************************/
#include "ann.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
   
   void ann::train(float *inpSet, float *outSet, int K, int Steps, bool show_error){
      
      int i,j,k;
      int Set;            // Selected set
      float *inp, *out;   // Desired output with provided input
      float *y;           // Network Layer output
      float *d0;          // Output error
      float *di;          // Interior error
      float *wp;          // Weights
      float *vp;          // Bias weights
      float *xp;          // Layer
      int Max = 0;
      int tmp;
      float err;
      
      for (i = 0; i < N-1; i++){
         tmp = LayerSizes[i]*LayerSizes[i+1];
         Max = (tmp > Max) ? tmp : Max;
      }
      
      float buf[Max];    // Buffer space
      
      float *dw, *dv;
      
      float Error;
      
      // Define the output error position
      d0 = d;
      for (k = 0; k < N-1; k++)
         d0 += LayerSizes[k];
      
      for (k = 0; k < Steps; k++){
      
         // Randomly select a training set
         Set = rand() % K;
         inp = inpSet + Set * LayerSizes[0];
         out = outSet + Set * LayerSizes[N-1];
         
         // Feed forward
         y = forward(inp);

         if (show_error) {
            err = 0.0;
            for (int k = 0; k < LayerSizes[N-1]; k++) {
               err += (y[k] - out[k])*(y[k] - out[k]);
            }
            err /= LayerSizes[N-1];
            err = sqrtf(err);
            std::cout << "Error = " << err << std::endl;
         }
         
         // Get the output error
         for (i = 0; i < LayerSizes[N-1]; i++)
            d0[i] = out[i] - y[i];
         
         // Define the interior layer position
         xp = x;
         for (i = 0; i < N-2; i++)
            xp += LayerSizes[i];
         
         // Define the interior error position
         di = d0 - LayerSizes[N-2];
      
         // Define the weights position
         wp = w;
         for (i = 0; i < N-2; i++)
            wp += LayerSizes[i] * LayerSizes[i+1];
         
         // Back propagate the error
         for (i = N-2; i > 0; i--){
         
            // Get the current layer error
            Tmult(&buf[0], wp, di + LayerSizes[i], LayerSizes[i+1], LayerSizes[i]);
            for (j = 0; j < LayerSizes[i]; j++)
               di[j] = buf[j] * beta * xp[j] * (1.0f - xp[j]);
            
            if (i > 0){ // maybe not needed
               // Move the interior layer position back one layer
               xp -= LayerSizes[i-1];
               
               // Move the interior error position back one layer
               di -= LayerSizes[i-1];
               
               // Move the weights position back one layer
               wp -= LayerSizes[i] * LayerSizes[i-1];
            }
            
         }
         
         di = d + LayerSizes[0];
         xp = x;
         wp = w;
         vp = v;
         
         // Update the weights
         for (i = 0; i < N-1; i++){
         
            // Get the weight changes
            dw = &buf[0];
            outer(dw, di, xp, LayerSizes[i+1], LayerSizes[i]);
            
            // Update the weights
            for (j = 0; j < LayerSizes[i] * LayerSizes[i+1]; j++)
               wp[j] += nu * dw[j];

            // Get the bias weight changes
            dv = &buf[0];
            for (j = 0; j < LayerSizes[i+1]; j++)
               dv[j] = di[j] * bias;
            
            // Update the bias weights
            for (j = 0; j < LayerSizes[i+1]; j++)
               vp[j] += nu * dv[j];
            
            // Move forward a layer
            di += LayerSizes[i+1];
            xp += LayerSizes[i];
            wp += LayerSizes[i] * LayerSizes[i+1];
            vp += LayerSizes[i+1];
         }

         Error = 0.0f;
         for (i = 0; i < LayerSizes[N-1]; i++)
            Error += d0[i]*d0[i];
      }
   }
