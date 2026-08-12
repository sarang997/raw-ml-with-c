#include <stdio.h> 
#include <math.h>
#include <stdlib.h>
#include "2D_matrix_mul.h"

//description: creating higher layer abstraction of creating 2D matrices and storing them in a struct Matrix
typedef struct{
  float *data;
  int R;
  int C;

} Matrix;

Matrix matrix_create(int R, int C){

  Matrix m1;
  m1.data = NULL;
  m1.C = 0;
  m1.R = 0;
  if(R<=0 || C<=0){
    return m1;
  }
  //if the dimensions are valid 
  m1.data = create_matrix(R,C);
  if(m1.data ==NULL){
    return m1;
  }
  m1.R = R; 
  m1.C = C;

  return m1;
}

void matrix_print(Matrix m){
   print_matrix(m.data, m.R, m.C);
}

void matrix_free(Matrix *m){

  free(m->data);
  m->R = 0;
  m->C = 0;
  m->data = NULL;
}

//int set(float *m, int C, int r, int c, float value);
int matrix_set(Matrix *m, int r, int c, float value){

  if(m == NULL || m->data==NULL || r <0 || c<0){
    return 0; 
  }
  if(r >= m->R || c >= m->C){

    return 0;
  }
   
  set(m->data, m->C,r,c,value);
  return 1; 
}
//pass the matrix, r,c and get the value at that position from the struct
int matrix_get(Matrix *m, int r, int c, float *value){
  if(m == NULL || m->data == NULL || r<0 || c<0 || value ==NULL){
    return 0;
  }
  if(r >=m->R || c >=m->C){
    return 0;
  }
  *value =  get(m->data, m->C, r, c);
  return 1; 
}

//fill the matrix with a value
int matrix_fill(Matrix *m, float value){
    if(m ==NULL || m->data == NULL){

     return 0; 
    }

   fill_matrix(m->data, m->R, m->C, value);  
    return 1;
}

Matrix matrix_add(Matrix *m, Matrix *n){
  Matrix result; 
  result.data = NULL;
  result.R = 0;
  result.C = 0;

  //check if data is not NULL R,C <0 
  if(m->data ==NULL || n->data ==NULL || m->R <0 || m->C <0 || n->R < 0 || n->C <0){
    return result;
  }
  //check if the r,c same for valid addition 
  if(m->R != n->R || m->C !=n->C){
    return result;
  }
  //call the add matrix 

 result.data = matrix_addition(m->data, n->data, m->R, m->C);
 result.R = m->R;
 result.C = m->C;

  return result; 
}

Matrix matrix_mul(Matrix *m, Matrix *n){
  Matrix result; 
  result.data = NULL;
  result.R = 0;
  result.C = 0;
  if(m->data == NULL || n->data == NULL || m->R <0 || m->C <0 || n->R <0 || n->C <0){
    return result;
  }
  
  //inner dimensions should match for a valid multiplcation
  if(m->C != n->R){
    return result;
  }

  result.data = matmul(m->data, n->data, m->R, m->C, n->C);
  result.R = m->R;
  result.C = n->C;
  return result;
}

int main(){ 

  int R = 2;
  int C = 3;
  Matrix m = matrix_create(R,C);
  Matrix n = matrix_create(R,C);
  Matrix r = matrix_create(C,R);
  //set value = 2.0 at 1,1 
  matrix_set(&m, 1,1, 2.0);
  float value;
  if(matrix_get(&m, 1,2, &value)){

    printf("value at 1,1 in matrix: %f\n", value);
  }
  else{
     printf("could not get the value\n");
     
  }
  matrix_fill(&m, 3.0);
  matrix_fill(&n, 2.0);
  matrix_fill(&r, 1.0);

  printf("matrix m: \n");
  matrix_print(m);
  printf("matrix n:\n");
  matrix_print(n);

  printf("addition m+n:\n");
  Matrix result = matrix_add(&m, &n);
  matrix_print(result);
  //matrix multiplcation 
  Matrix result_mul = matrix_mul(&m, &r);
  printf("multiplication m*r:\n");

  matrix_print(result_mul);
  matrix_free(&m);
  matrix_free(&n);

  return 0;
}
