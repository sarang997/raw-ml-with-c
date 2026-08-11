#include <stdio.h>
#include <stdlib.h>
#include "2D_matrix_mul.h"

//function for allocating memory on the heap
float *create_matrix(int R, int C){
  //allocation memory R*C to the heap and return the pointer 
  float *m = malloc(R* C * sizeof(float));
  for(int i=0; i< R*C; i++){
    m[i] = 0;
  }
  return m;
}

//function for setting the value in a matrix
int set(float *m, int C, int r, int c, float value){

    int idx = r * C + c;
    m[idx] = value;
  return idx;
}
//function for getting the value from index 
float get(float *m, int C, int r, int c){

  return m[r*C+c];
}

//function fills the values starting from 0 to the matrix
void fill_sequential(float *m, int R, int C){

  for(int i=0; i< R*C; i++){
    m[i] = i;
  }
}

void fill_matrix(float *m, int R, int C, float value){
   
  for(int i=0; i< R*C; i++){
    m[i] = value;
  }
}

//function for multiplying 2D matrics- A -> M K B-> K N
float *matmul(float *A, float *B, int M, int K, int N){
    
    float *result = malloc(M*N*sizeof(float));

    for(int i=0; i<M; i++){
      for(int j=0; j<N; j++){
        float sum = 0;
        for(int k=0; k<K; k++){
            
         sum += A[i*K + k] * B[k*N+j];
        }
        //set the value in the result matrix
        set(result, N, i, j, sum);
      }
    }
    return result;
}

//function for matrix addition. input-> the input matrix is A and B 
float *matrix_addition(float *A, float *B, int M, int N){
  
  //allocating new memory for the the resulting matrix 
  float *result = malloc(M*N*sizeof(float));
  
  //looping over and adding elementwise
  for(int i=0;i<M*N; i++){
    result[i] = A[i] + B[i];
  }
  return result;
}

//scalar multiply every element with a number
float *scalar_multiply(float *m, int M, int N, float value){
    
    float *result = malloc(M*N*sizeof(float));
    for(int i=0; i< M*N; i++){
       result[i] = m[i] * value; 
    }
    return result;

}
//M N matrix is transposed to N M and pointer is returned
float *transpose(float *m, int M, int N){

  float *result = malloc(M*N*sizeof(float));
  //transposr M by N to N by M 
  for(int i=0; i<M; i++){
    for(int j=0; j<N; j++){
      result[j*M+i] = m[i*N+j];
    }
  }
  return result;
}

float *identity(int N){

  float *result = calloc(N*N,sizeof(float));
  for(int i=0; i<N; i++){
     // 00 , 11, 22, 33 i +i*N
     result[i+i*N] = 1; 
  } 
  return result;
}
float *sum_along_rows(float *m, int R, int C){
  float *output = malloc(R*sizeof(float)); 
  for(int i=0; i<R; i++){
    float sum =  0; 
    for(int j=0; j<C; j++){
      sum+= m[i*C + j];
    }
    output[i] = sum;
  }
  return output;
}
void print_matrix(float *m, int M, int N){

  for(int i=0; i<M; i++){
   for(int j=0; j<N; j++){
     printf("%f  ", m[i*N+j]);
   } 
    printf("\n");

  }
}

