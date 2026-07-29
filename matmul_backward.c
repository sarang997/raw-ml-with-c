#include <stdio.h>
#include "2D_matrix_mul.h"
#include <stdlib.h> 

void matmul_backward(float *dC, float *A, float *B, float *dA, float *dB, int M, int N, int K){
    // A -> M K 
    // B-> K N 
    //dA = dC @ B.T
   float *BT = transpose(B, K, N);
   float *dA_computed  = matmul(dC, BT,M, N, K);

   float *AT = transpose(A,M,K);
   float *dB_computed = matmul(AT, dC, K, M, N);

   for(int i =0; i< M*K; i++) dA[i] = dA_computed[i];
   for(int i =0; i< K*N; i++) dB[i] = dB_computed[i];

   //free up the memory for the intermediate buffers
   free(dA_computed); free(dB_computed);
   free(AT); free(BT);
}

int main(){

  int M =2; 
  int N = 2;
  int K = 2; 
  //creating variables for testing
  float dC[] = {1,1,1,1};
  float A[] = {1,2,3,4};
  float B[] = { 5,6,7,8};
  float *dA = malloc(M*K*sizeof(float));
  float *dB = malloc(K*N*sizeof(float));

  matmul_backward(dC,A,B, dA,dB, M, N, K);
  print_matrix(dA, M, K);
  return 0;
}

