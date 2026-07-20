#include <stdio.h>
#include <stdlib.h>


float *malloc_matrix(int R, int C){
  //allocation memory R*C to the heap and return the pointer 
  float *m = malloc(R* C * sizeof(float));
  for(int i=0; i< R*C; i++){
    m[i] = 0;
  }
  return m;
}

int set(float *m, int C, int r, int c, float value){

    int idx = r * C + c;
    m[idx] = value;
  return idx;
}

float get(float *m, int C, int r, int c){

  return m[r*C+c];
}

//function fills the values starting from 0 to the matrix
void fill_sequential(float *m, int R, int C){

  for(int i=0; i< R*C; i++){
    m[i] = i;
  }
}

float *matmul(float *A, float *B, int M, int K, int N){
    
    float *result = malloc_matrix(M,N);

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

//main entry point function 
int main(){
  //number of rows and columns defined 
  int R = 3;
  int C = 3; 

  //function for allication memory take R and C input 
  float *m = malloc_matrix(R,C);
  float *n = malloc_matrix(R,C);

  //set function to set the value of the matrix 
  int r = 1;
  int c = 1;
  float value = 2.0;
  int set_index = set(m, C, r,c, value);
  printf("index of set value is: %d\n", set_index);
  
  //get function
  float get_value = get(m, C, 0, c); 
  
  //filling seqential values to the array 
  fill_sequential(m, R, C);
  fill_sequential(n,R,C);

  //function for multiplying 2 matrix -> M*K and K*N matrix
  int M = 3; 
  int K = 3; 
  int N = 3;
  float *result = matmul(m, n, M, K, N );
  printf("result after matrix multiplication: %f\n", get(result,N,1,1)); // should print 54.00
  
  //freeing the memory 
  free(m); free(n); free(result);
  return 0;
}
