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

//helper function for checking validity
int matrix_is_valid(Matrix *m){
  if(m!=NULL && m->data != NULL && m->R > 0 && m->C >0){
    return 1;
  }
  return 0;
}

//create a matrix
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
//function for printing the matrix
void matrix_print(Matrix m){
   print_matrix(m.data, m.R, m.C);
}

int matrix_free(Matrix *m){
  if(m==NULL){
    return 0; 
  }
  free(m->data);
  m->R = 0;
  m->C = 0;
  m->data = NULL;
  return 0;
}

//int set(float *m, int C, int r, int c, float value);
int matrix_set(Matrix *m, int r, int c, float value){

  if(!matrix_is_valid(m) || r <0 || c<0){
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
  if(!matrix_is_valid(m) || r<0 || c<0 || value ==NULL){
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
  if(!matrix_is_valid(m)){
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
  if(!matrix_is_valid(m) || !matrix_is_valid(n)){
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

Matrix matrix_sub(Matrix *m, Matrix *n){
  Matrix result; 
  result.data = NULL;
  result.R = 0;
  result.C = 0;

  //check if data is not NULL R,C <0 
  if(!matrix_is_valid(m) || !matrix_is_valid(n)){
    return result;
  }
  //check if the r,c same for valid addition 
  if(m->R != n->R || m->C !=n->C){
    return result;
  }

  //call the substraction function 
  result.data = matrix_substraction(m->data, n->data, m->R, m->C);
  result.R = m->R;
  result.C = m->C;

  return result; 
}

Matrix matrix_mul(Matrix *m, Matrix *n){
  Matrix result; 
  result.data = NULL;
  result.R = 0;
  result.C = 0;
  if(!matrix_is_valid(m) || !matrix_is_valid(n)){
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

//matrix transpose
Matrix matrix_transpose(Matrix *m){
  Matrix result;
  result.data = NULL;
  result.R = 0;
  result.C = 0;
  if(!matrix_is_valid(m)){
    return result;
  }
  result.data = transpose(m->data, m->R, m->C);
  result.R = m->C;
  result.C = m->R;

  return result;
}

//scalar multiplication wrapper for a 2D matrix
Matrix matrix_scalar_mul(Matrix *m, float value){

  Matrix result;
  result.data = NULL;
  result.R = 0;
  result.C = 0; 

  if(!matrix_is_valid(m)){
     return result; 
  }

  result.data = scalar_multiply(m->data, m->R, m->C, value);
  result.R = m->R;
  result.C = m->C;

  return result;
}

//elementwise multiplication 
Matrix matrix_elementwise_mul(Matrix *m, Matrix *n){
  Matrix result;
  result.data = NULL;
  result.R = 0;
  result.C = 0;
  

  if(!matrix_is_valid(m) || !matrix_is_valid(n)){
    return result;
  }
  if(m->R != n->R || m->C != n->C){
    return result;
  }
  //TODO complete the validation checks in this.. 

  result.data = elementwise_mul(m->data, n->data, m->R,m->C);
  result.R = m->R;
  result.C = m->C;

  return result;
}
//helper function for checking if Matrix struct is valid

Matrix matrix_copy(Matrix *m){
  Matrix m_copy; 
  m_copy.data = NULL;
  m_copy.R = 0;
  m_copy.C = 0;
  if(!matrix_is_valid(m)){
    return m_copy;
  }
  m_copy = matrix_create(m->R, m->C);
  //copy the data from m to n
  for(int i=0; i<m->R;i++){
    for(int j=0; j<m->C;j++){
      m_copy.data[i*m->C + j] = m->data[i*m->C + j];
    }
  }
 m_copy.R = m->R;
 m_copy.C = m->C;

 return m_copy;
}

int main(){ 
  //testing the functions
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
  
  //transpose
  printf("transpose:\n");
  Matrix transposed = matrix_transpose(&r);

  matrix_print(result_mul);
  
  printf("before transpose:\n");
  matrix_print(r);
  printf("after transpose:\n");
  matrix_print(transposed);

  //scalar mul matrix
  float  scalar = 10.0;
  Matrix scalar_mul_result = matrix_scalar_mul(&r,scalar);
  matrix_print(scalar_mul_result);
  //copying the matrix
  Matrix r_copy = matrix_copy(&r);
  printf("pointer of r: %p: \n", &r);
  printf("pointer of r_copy: %p: \n", &r_copy); // should print different pointer adresses
  //freeing the matrics 
  matrix_free(&m);
  matrix_free(&n);
  matrix_free(&r);
  matrix_free(&scalar_mul_result);
  matrix_free(&transposed);
  matrix_free(&result_mul);
  matrix_free(&result);
  
  return 0;
}
