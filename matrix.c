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
  m1.data = create_matrix(R,C);
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
void matrix_set(Matrix *m, int r, int c, float value){
  set(m->data, m->C,r,c,value);
}
//pass the matrix, r,c and get the value at that position from the struct
float matrix_get(Matrix *m, int r, int c){

  return get(m->data, m->C, r, c);
}

int main(){ 
  int R = 2;
  int C = 3;
  Matrix m = matrix_create(R,C);
  matrix_print(m);
  //set value = 2.0 at 1,1 
  matrix_set(&m, 1,1, 2.0);
  printf("value at 1,1 in matrix: %f\n", matrix_get(&m, 1,1));
  printf("value at 0,1 in matrix: %f\n", matrix_get(&m, 0,1));
  matrix_free(&m);

  return 0;
}
