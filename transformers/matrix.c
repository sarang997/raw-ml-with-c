#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "matrix.h"
//Allocate heap memory + plus rows and cols
int Matrix_alloc(Matrix *M, int rows, int cols){

  if(M==NULL) return 0;

  M->data = malloc(rows*cols*sizeof(float));
  M->rows = rows;
  M->cols = cols;
  if(M->data==NULL) return 0;

  return 1;
}

int Matrix_create_random(Matrix *M, int rows, int cols){

  if(rows<=0 || cols<=0) return 0;
  if (M->data==NULL) return 0; //no memory assignment found
  M->rows = rows;
  M->cols = cols;
  //allocation not needed here it should be done my separate func (better design) 
  //M->data = malloc(rows*cols*sizeof(float));
                               //
  for(int i=0; i<rows*cols; i++){
    float random_val = ((float)rand() / (float)RAND_MAX) *0.2f -0.1f;
    M->data[i] = random_val;
  }
  return 1;
}

// INITIALIZE MODEL WEIGHTS
int Transformer_initialize_weights(TransformerModel *model){

  // loop through the layers 
  // for each layer initialise its Q,K,V weights
  int num_layers = model->num_layers;
  int d_model = model->d_model;
  
  for(int i=0; i<num_layers ;i++){

    // call matrix_alloc for each of the weights 
    Matrix_alloc(&model->layers[i].attention.Q_W, d_model, d_model);
    Matrix_alloc(&model->layers[i].attention.K_W, d_model, d_model);
    Matrix_alloc(&model->layers[i].attention.V_W, d_model, d_model);

    // create random weights 
    Matrix_create_random(&model->layers[i].attention.Q_W, d_model, d_model);
    Matrix_create_random(&model->layers[i].attention.K_W, d_model, d_model);
    Matrix_create_random(&model->layers[i].attention.V_W, d_model, d_model);
     
  }
  printf("Initialized weights for all layers \n");
  return 1;
}
int Matrix_addition(Matrix *A, Matrix *B, Matrix *out){
 // checks
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
  
int LayerNorm(Matrix *M, int d_model, Matrix *out){
  if(M==NULL || M->data==NULL) return 0;
  if(M->rows <=0 || M->cols<=0) return 0; 
  if(d_model<=0 || M->cols !=d_model) return 0;
  //take each row: fins mean and variance then normaize each value
  
  float eps = 1e-5f;
  for(int i=0; i<M->rows; i++){
  
    //mean
    float mean = 0.0f;
    float variance = 0.0f; 
    for(int j=0; j<d_model; j++){
      mean+=M->data[i*M->cols+j];
    }
    mean /= d_model;

    //variance
    for(int k=0; k<d_model; k++){
      float diff = M->data[i*M->cols+k] - mean; 
      variance += diff*diff;
    }
    variance /=d_model;
  
    //standardise
    float inv_std = 1.0f / sqrtf(variance+eps);
    for(int j=0; j<d_model; j++){
      float x = M->data[i*d_model+j];
      out->data[i*d_model+j] = (x-mean) * inv_std;
    }
  }
  return 1; 
}
//ATTENTION FORWARD
Matrix *single_head_attention_forward(Matrix *input, TransformerLayer *layer, LayerCache *cache, int d_model, int residual_connection){
  int d_k = input->cols;

  //create weights for Q, K, V
  //Matrix Q_W, K_W, V_W;
  //Matrix_create_random(&Q_W, d_model, d_model);
  //Matrix_create_random(&K_W, d_model, d_model);
  //Matrix_create_random(&V_W, d_model, d_model);
  //printf("created weights\n");

  //create Q,K,V and allocate space
  Matrix Q,K,V, K_transpose, scores, soft_scores;
  Matrix_alloc(&Q, input->rows, d_k);
  Matrix_alloc(&K, input->rows, d_k);
  Matrix_alloc(&V, input->rows, d_k);

  //calculate Q,K,V
  Matrix_mul(input, &layer->attention.Q_W, &Q);
  Matrix_mul(input, &layer->attention.K_W, &K);
  Matrix_mul(input, &layer->attention.V_W, &V);

  printf("calculated Q,K,V\n");

 //scores = Q.K^T
  Matrix_alloc(&K_transpose, K.cols, K.rows);
  Matrix_transpose(&K, &K_transpose);

  Matrix_alloc(&scores, Q.rows, K_transpose.cols);
  Matrix_mul(&Q, &K_transpose, &scores);

  //divide scores by sqrt(d_k)
  float scale = 1.0f / sqrtf((float)d_k);
  Matrix_mul_scalar(&scores, &scores, scale);
  printf("calculated scores\n");
  //softmax
  Matrix_alloc(&soft_scores, scores.rows, scores.cols);
  Matrix_softmax(&scores, &soft_scores, 0);
  printf("calculated softmax scores\n");
  
  //layer normalization
  Matrix out1; 
  Matrix_alloc(&out1, input->rows, input->cols);

  //allocate memory for output in LayerCache
  Matrix_alloc(&cache->out, input->rows, input->cols);
  //residual connection 
  if(residual_connection!=1){

    Matrix_mul(&soft_scores, &V, &out1);
    LayerNorm(&out1, d_model, &cache->out);
    cache->out.rows = input->rows;
    cache->out.cols = input->cols;

  }
  else{
       //soft_scores.V -> gives actual input shape
    Matrix_mul(&soft_scores, &V, &out1);
    out1.rows = input->rows;
    out1.cols = input->cols;
   
    Matrix_addition(&out1, input, &out1);
    LayerNorm(&out1, d_model, &cache->out);
    cache->out.rows = input->rows;
    cache->out.cols = input->cols;

  }
  //freee up heap for intermediate matrices
  Matrix_free(&Q); Matrix_free(&K); Matrix_free(&V); Matrix_free(&K_transpose); Matrix_free(&scores); Matrix_free(&soft_scores); Matrix_free(&out1); 
  
  printf("calculated out\n");
  Matrix_print(&cache->out);
  return &cache->out;
}

#ifdef MATRIX_TEST
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
  Matrix_create_random(&input, 12, 72);
    
  //single_head_attention_forward(&input, d_model, 1, &out);
  //printf("final output!! \n");
  //Matrix_free(&out); Matrix_free(&input);
  
  // CREATE MODEL 
  // TransformerModel model;
  // model.num_layers = 3;
  // model.d_model = 4;

  // assign layer heap memory and initialize weights.
  // model.layers = malloc(model.num_layers * sizeof(TransformerLayer)); 
  // Transformer_initialize_weights(&model);

  //print few weight matrices
  // Matrix_print(&model.layers[2].attention.Q_W);
  return 0;

}

#endif
