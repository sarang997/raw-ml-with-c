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

        out->data[j*A->rows+i] = A->data[i*A->cols+j];      
    }

  }
  //assign the rows and the columns
  out->rows = A->cols;
  out->cols = A->rows;
  return 1;
}

int Matrix_mul(Matrix *A, Matrix *B, Matrix *out){
    if(A==NULL || B==NULL || out==NULL) return 0;

    if(A->cols != B->rows) return 0; 

    if(out->rows != A->rows || out->cols != B->cols) return 0;

    for(int r=0; r<A->rows; r++){
      for(int p=0; p<B->cols; p++){

        float sum=0.0;
        for(int c=0; c<A->cols; c++){
           sum += A->data[r*A->cols+c] * B->data[c*B->cols+p];
       }
        out->data[r*out->cols+p]=sum;
      } 
    }
    out->rows = A->rows;
    out->cols = B->cols;
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
int Matrix_create_ones(Matrix *M, int rows, int cols){
    if(rows<=0 || cols<=0) return 0;
    M->rows = rows;
    M->cols = cols; 
    M->data = malloc(rows*cols*sizeof(float));
    if(M->data == NULL) return 0; //memory allocation failure

    for(int i=0; i<rows*cols; i++){
      M->data[i] = 1;
    }
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
    float random_val = ((float)rand() / (float)RAND_MAX) *0.2f -0.1f;
    M->data[i] = random_val;
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

//Allocate heap memory + plus rows and cols
int Matrix_alloc(Matrix *M, int rows, int cols){

  if(M==NULL) return 0;

  M->data = malloc(rows*cols*sizeof(float));
  M->rows = rows;
  M->cols = cols;
  if(M->data==NULL) return 0;

  return 1;
}

int Matrix_print(Matrix *M){

  for(int i=0; i<M->rows; i++){
    for(int j=0; j<M->cols; j++){
      printf("%f ", M->data[i*M->cols+j]);
    }
    printf("\n");
  }
    printf("\n");
  return 1; 
}

//MATRIX FREE
void Matrix_free(Matrix *M){
  if(M!=NULL){
    free(M->data);
    M->data = NULL; //good practice to set it to NULL 
  }
  M->rows=0;
  M->cols=0;
  }

//ATTENTION FORWARD
Matrix *single_head_attention_forward(Matrix *input, int d_model, int residual_connection, Matrix *out){
  printf("input\n");
  Matrix_print(input);
  int d_k = input->cols;
  //create weights for Q, K, V
  Matrix Q_W, K_W, V_W;
  Matrix_create_random(&Q_W, d_model, d_model);
  Matrix_create_random(&K_W, d_model, d_model);
  Matrix_create_random(&V_W, d_model, d_model);
  printf("created weights\n");
  Matrix_print(&Q_W);
  Matrix_print(&K_W);
  Matrix_print(&V_W);
  //create Q,K,V and allocate space
  Matrix Q,K,V, K_transpose, scores, soft_scores;
  Matrix_alloc(&Q, input->rows, d_k);
  Matrix_alloc(&K, input->rows, d_k);
  Matrix_alloc(&V, input->rows, d_k);

  //calculate Q,K,V
  Matrix_mul(input, &Q_W, &Q);
  Matrix_mul(input, &K_W, &K);
  Matrix_mul(input, &V_W, &V);

  printf("calculated Q,K,V\n");
  Matrix_print(&Q);

 //scores = Q.K^T
  Matrix_alloc(&K_transpose, K.cols, K.rows);
  Matrix_transpose(&K, &K_transpose);

  Matrix_alloc(&scores, Q.rows, K_transpose.cols);
  Matrix_mul(&Q, &K_transpose, &scores);

  printf("calculated scores\n");
  //softmax
  Matrix_alloc(&soft_scores, scores.rows, scores.cols);
  Matrix_softmax(&scores, &soft_scores, 0);
  printf("calculated softmax scores\n");

  //allocate memory for output data
  Matrix_alloc(out, input->rows, input->cols);
  //residual connection 
  if(residual_connection!=1){

    Matrix_mul(&soft_scores, &V, out);
    out->rows = input->rows;
    out->cols = input->cols;

  }
  else{
    Matrix out1; 
    Matrix_alloc(&out1, input->rows, input->cols);
   //soft_scores.V -> gives actual input shape
    Matrix_mul(&soft_scores, &V, &out1);
    out1.rows = input->rows;
    out1.cols = input->cols;
   
    Matrix_addition(&out1, input, out);
    out->rows = input->rows;
    out->cols = input->cols;
    Matrix_free(&out1); 

  }
  //freee up heap for intermediate matrices
  Matrix_free(&Q); Matrix_free(&K); Matrix_free(&V); Matrix_free(&K_transpose); Matrix_free(&scores); Matrix_free(&soft_scores);
  
  printf("calculated out\n");
  return out;
}
//main function 
int main(){
  
  Matrix M;
  Matrix_create_random(&M, 5,5);
  // Matrix_print(&M);

  //testing matrix mul 
  //Matrix A, B, mul_out;
  //Matrix_create_ones(&A, 5,4);
  //Matrix_create_ones(&B, 4,5);
  //Matrix_alloc(&mul_out, 5,5);
  //Matrix_mul(&A, &B, &mul_out); 
  //printf("returned value: %d", Matrix_mul(&A, &B, &mul_out));
  //free memory from heap
  //Matrix_free(&M); Matrix_free(&A); Matrix_free(&B); Matrix_free(&mul_out);
  
  //testing the forward attention block 
  int d_model = 72; //embedding dimension 
  Matrix input, out;
  Matrix_create_random(&input, 256, 72);
  
  single_head_attention_forward(&input, d_model, 1, &out);
  printf("final output!! \n");
  Matrix_print(&out);
  return 0;

}
