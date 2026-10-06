#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

//defining a Matrix struct 
typedef struct{
  int rows;
  int cols;
  float *data;

} Matrix;

typedef struct{
  Matrix Q_W;
  Matrix K_W;
  Matrix V_W;

} Q_K_V_weights;

//Utils Functions required for forward pass
int Matrix_addition(Matrix *A, Matrix *B, Matrix *out){
  //checks
  if(A==NULL || B==NULL || out==NULL) return 0;
  if(A->rows != B->rows || A->cols !=B->cols) return 0;

  out->rows = A->rows;
  out->cols = A->cols;

  for(int i=0; i<A->rows * A->cols; i++){
      out->data[i] = A->data[i] + B->data[i];
  }
  return 1;
}

int Matrix_transpose(Matrix *A, Matrix *out){
  if(A==NULL || out==NULL) return 0;
  
  for(int i=0; i<A->rows; i++){
    for(int j=0; j<A->cols; j++){

        out->data[j*out->cols+i] = A->data[i*A->cols+j];      
    }

  }
  return 1;
}

int Matrix_mul(Matrix *A, Matrix *B, Matrix *out){
    
    for(int r; r<A->rows; r++){
      for(int c; c<A->cols; c++){
         //out->data[] = A->data[r*A->rows+c] * B->data[c*B->cols_r];
      }
    }
  return 1;
}

int Matrix_softmax(Matrix *A, Matrix *out, int axis){
  if(A==NULL || out ==NULL) return 0;
  //if axis = 0 row wise of 1 column wise (just need row-wise for now)
  //along rows 
  if(axis==0){
    for(int r=0; r<A->rows;r++){
      //STEP 1: find max of row 
      float max_val = -FLT_MAX;
      for(int c=0; c<A->cols;c++){
        if(A->data[r*A->cols+c] > max_val){
          max_val = A->data[r*A->cols+c];
        }
      }

     //STEP 2: find the sum of the row with substracting max for numerical stability
     float sum = 0.0;
     for(int c=0; c<A->cols;c++){
        sum+=exp(A->data[r*A->cols+c] - max_val);
    }
    //STEP 3: find the softmax for each row value
    for(int d=0; d<A->cols; d++){
      out->data[r*out->cols + d] = exp(A->data[r*A->cols+d] - max_val)/sum;
    }
    }
  out->rows = A->rows;
  out->cols = A->cols;
  return 1;
}
if(axis==1){
//TODO
  return 1;
}
return 0;
}

int Matrix_mul_scalar(Matrix *A, Matrix *out, float s){
  //checks
  if(A==NULL || out==NULL) return 0;
  
  for(int i=0; i<A->rows * A->cols; i++){
      out->data[i] = s * A->data[i];
  }

out->rows = A->rows;
out->cols = A->cols;

  return 1;
}

int Matrix_create_random(Matrix *M, int rows, int cols){

  if(rows<=0 || cols<=0) return 0;

  M->rows = rows;
  M->cols = cols;
  
  M->data = malloc(rows*cols*sizeof(float));
  if (M->data==NULL) return 0; //malloc assignment failure
                               //
  for(int i=0; i<rows*cols; i++){
    float random_0_to_1 = (float)rand() / (float)RAND_MAX;
    M->data[i] = (random_0_to_1*0.2f) / -0.1f;
  }
  return 1;
}
//for now create the random numbers needed for the transformer
int create_Q_K_V_weights(Q_K_V_weights *weights, int d_model){
  if(weights==NULL) return 0;

  Matrix_create_random(&weights->Q_W, d_model, d_model);
  Matrix_create_random(&weights->K_W, d_model, d_model);
  Matrix_create_random(&weights->V_W, d_model, d_model);
    
  return 1;
}

int Matrix_alloc(Matrix *M, int rows, int cols){

  if(M==NULL) return 0;

  M->data = malloc(rows*cols*sizeof(float));
  if(M->data==NULL) return 0;

  return 1;
}

float *single_head_attention_forward(Matrix *input, Q_K_V_weights *weights, int d_model){
  Matrix Q,K,V;
  //Matrix_alloc(&Q,);
  Matrix_mul(input, &weights->Q_W, &Q);
 //Q = input * Q_W, K = input * Q_K, V = input * Q_V
 //scores = Q.K^T
 //soft_scores = softmax(scores)
 //soft_scores.V -> gives actual input shape
 //return this new Matrix pointer
 return NULL;
}
//main function 
int main(){

  return 0;

}
