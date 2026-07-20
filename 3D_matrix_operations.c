#include <stdio.h>
#include <stdlib.h> 

// B -> batch size 
// T -> time (sequence length of words)
// C -> number of channels (embedding dimensions)

//function for getting a float value from 3D tensor
float get3D(float *data, int T, int C, int b, int t, int c){

    return data[b*(T*C) + t*C+c];
}

//function for setting the float value in a 3D tensor
void set3D(float *data, int T, int C, int b, int t, int c, float value){

  int idx = b*(T*C) + t*C+c;
  data[idx] = value;
}
//filling the tensor with some values
void fill_tensor(float *data, int B, int T, int C){
    for(int b = 0; b < B; b++){
        for(int t = 0; t < T; t++){
            for(int c = 0; c < C; c++){
                set3D(data, T, C, b, t, c, b*100 + t*10 + c);
            }
        }
    }
}

void print_tensor(float *data, int B, int T, int C){

    for(int b = 0; b < B; b++){
        printf("Batch %d\n", b);

        for(int t = 0; t < T; t++){
            for(int c = 0; c < C; c++){
                printf("%f ", data[b * (T * C) + t * C + c]);
            }
            printf("\n");
        }

        printf("\n");
    }
}
int main(){
  int B = 2; 
  int T = 3; 
  int C = 4; 

  float *data = calloc(B*T*C, sizeof(float));
  fill_tensor(data,B,T,C);
  set3D(data, T, C, 0, 2,2, 2.0);
  print_tensor(data, B, T, C);

  
  free(data);
return 0; 
}
