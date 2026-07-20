#include <stdio.h>
#include <stdlib.h>

//function for allocating memory on the heap
float *malloc_matrix(int R, int C){
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

//function for multiplying 2D matrics
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

void print_matrix(float *m, int M, int N){

  for(int i=0; i<M; i++){
   for(int j=0; j<N; j++){
     printf("%f  ", m[i*N+j]);
   } 
    printf("\n");

  }
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
 
  // matrix addition testing
  float *added_result = matrix_addition(m,n,R,C);  
  printf("added matrix result: el1: %f | el2: %f\n", get(added_result,N,0,0),get(added_result,N,0,1));

  //scalar multiplication of matrix
  float *scalar_multiplied = scalar_multiply(m, R,C, 10);
printf("scalar multiply: %f\n", get(scalar_multiplied,N,0,1)); //should print 10.00
  float *transposed = transpose(m, R, C);
  printf("transposed element check: %f\n", get(transposed,R, 1, 2)); // should print 7.00
  
  //identity matrix 
  float *iden = identity(3);
  print_matrix(scalar_multiplied,R,C);
  
  //freeing the memory 
  free(m); free(n); free(result); free(added_result); free(scalar_multiplied); free(transposed); free(iden);
    
  return 0;
}
