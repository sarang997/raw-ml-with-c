#include <stdio.h>
#include <stdlib.h>

int sum_of_array(int *arr1, int n){
  int sum =0;
  for(int i=0; i<n; i++){
     sum+= arr1[i]; 
  };
  return sum; 
}

float* make_zeros(int size){
  float *buf = calloc(size, sizeof(float));
  return buf;
}

void free_buffer(float *buf){

  free(buf);
}
int main(){
  //PROBLEM 1 - allocating the memory for 10 integers array 
  int *arr = calloc(10, sizeof(int));
    for(int i=0; i<10;i++){

      arr[i] = i;
    };

  free(arr);

  //PROBLEM 2- create n integer array 
  //write a function to take pointer to arr and n and return sum free memory 
  int n = 10; 
  int *arr1 = calloc(n, sizeof(int));
  for(int i=0; i<10;i++){
      arr1[i] = i;
    };
  int sum = sum_of_array(arr1, n);
  printf("the sum of array: %d\n", sum);
  free(arr1);
  //PROBLEM 3 - calloc vs malloc 
  int *arr2 = malloc(5 * sizeof(int));
  int *arr3 = calloc(5, sizeof(int));
  
  for(int i = 0; i<5;i++){
    printf("malloc array: %d | ", arr2[i]);
    printf("calloc array: %d\n", arr3[i]);
  };
  free(arr2);
  free(arr3);

//PORBLEM 4- realloc 
  int *arr4 = malloc(5 * sizeof(int));
  for(int i=0;i<5;i++){
    arr4[i]=i;
  };
  arr4 = realloc(arr4, 10 * sizeof(int));
  for(int i =5; i<10; i++){
    arr4[i] = i;
  };
  for(int i=0;i<10; i++){
    printf("%d\n", arr4[i]);
  }
  //remember to freet he memory when the heap assignment is done
  free(arr4);

//PROBLEM- 5 growable buffer 
  int size = 1000; 
  float *buf = make_zeros(size);
  printf("%f %f %f\n", buf[0], buf[1], buf[999]);

  free_buffer(buf);

  return 0; 
}







