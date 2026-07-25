#include <stdio.h> 
#include <stdlib.h> 
#include <float.h>
#include <math.h>
#include "2D_matrix_mul.h"

float *softmax(float *m, int R, int C){
      float *output = malloc(C*R*sizeof(float));
      for(int i=0; i<R;i++){
        float max = -FLT_MAX;
        float *normalized_row = malloc(C*sizeof(float));
      //find the max in this row 
        for(int j=0; j<C;j++){
          if(m[i*C+j] > max){
            max = m[i*C+j];
          }
        }
        float sum = 0;
        for(int k=0; k<C; k++){
          normalized_row[k]=max - m[i*C+k];
          sum += expf(normalized_row[k]);
         }
        for(int l=0; l<C;l++){
          output[i*C + l] = expf(normalized_row[l]) / sum;
        } 
        free(normalized_row);
        }
      return output;

}
int main(){ 
  int R = 5;
  int C = 5;
  float *m = create_matrix(R, C); 
  fill_sequential(m, R,C);
  float *output = softmax(m, R, C);
  print_matrix(output, R, C);
  float *sum_rows = sum_along_rows(output, R, C);
  print_matrix(sum_rows, R, 1);
return 0;
}
