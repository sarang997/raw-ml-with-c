#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include "2D_matrix_mul.h"
#define EPS 1e-5f

//function for normalizing each row multiplying by gamma and adding beta to it
//normalizing -> making sure the mean is 0 and variance 1 for entire row
float *layernorm_forward(float *x, float *gamma, float *beta, int R, int C){
   //allocation memory for output normalized  
   float *out = malloc(R*C*sizeof(float));
  for(int i=0; i<R; i++){

     //find mean of each row 
      float row_sum=0;
      for(int j=0; j<C; j++){
          row_sum+= x[i*C + j];
      }
      float mean = row_sum/C;

      //find variance 
      float squared_deviation = 0;
      for(int k=0; k<C; k++){
        squared_deviation+= (x[i*C+k]-mean) * (x[i*C +k]-mean);
      }
      float variance = squared_deviation/C;
      float std = sqrt(variance + EPS);

      //adding the normalized values to out and multiplying by gamma and adding beta
      for(int k=0; k<C; k++){
        out[i*C+k] = ((x[i*C + k]-mean) / std) * gamma[k] + beta[k];
      }
    }

  return out;

}
int main(){
  float x[] = {1,2,3,4,5,6};
  float gamma[] = {1,1,1,1,1,1};
  float beta[] = {0,0,0,0,0,0};
  int R = 2;
  int C = 3;
  float *out = layernorm_forward(x, gamma, beta, R, C);
  print_matrix(out, R ,C);
  free(out);
  return 0;
}
