#ifndef MATRIX_MUL_H
#define MATRIX_MUL_H

float *create_matrix(int R, int C);
void fill_sequential(float *m, int R, int C);
void print_matrix(float *m, int M, int N);
float *sum_along_rows(float *m, int R, int C);
float *transpose(float *m, int M, int N);
float *matmul(float *A, float *B, int M, int K, int N);
#endif
