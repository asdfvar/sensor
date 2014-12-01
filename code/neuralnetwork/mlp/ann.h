#ifndef _ANN_H_
#define _ANN_H_

class ann{
   public:

      int *LayerSizes;   // Array specifying the number of nodes for each layer

     /***************
      * Constructors
      ***************/

      ann(int *LayerSizes, int N, float bias, float beta, float nu);
      ~ann();
      
     /************
      * Functions
      ************/
      
      // Propagate the input forward in the network.
      // Returns a pointer to the output of the network.
      float *forward(float *inp);
      
      // Train the network with K input and corresponding
      // output sets
      void train(float *inpSet, float *outSet, int K, int Steps, bool show_error);

   private:
   
      float bias;     // Bias term
      float beta;     // Beta term
      float nu;       // Learning rate
      int N;          // Number of layers
      
      float *x;       // Layers
      float *w, *v;   // Weights w and bias weigts v
      float *d;       // Back propagation error arrays
      
      float *buf;     // buffer
      
      // Sigmoid function
      float g(float z, float beta);
      
     /************************
      * Some useful functions
      ************************/
      
      // Apply a matrix to a vector
      void mult(float *y, float *A, float *b, int M, int N);
      
      // Apply the transpose of a matrix to a vector
      void Tmult(float *y, float *A, float *b, int M, int N);
      
      // Apply the outer product of two vectors
      void outer(float *z, float *x, float *y, int M, int N);
      
};

#endif
