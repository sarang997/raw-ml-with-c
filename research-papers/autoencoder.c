#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//DENSE AUTOENCODER IMPLEMENTATION
//autoencoder steps:
  //encoder block: 
    //input = image (C,H,W) -- 3 channels for now 
    //output = latent vector in the latent space 
    //design-> create an Encoder object and pass it to the encoder_forward
    //encoder object -> input_size of image C*W*H, latent_size (size of latent vector)
    //Layer object -> contains input and output sizes of the layer, weights and bias floats
 
typedef struct{
  int input_size;
  int output_size;
  float *weights; 
  float *bias;
} Layer;

typedef struct{
  int latent_size;
  int num_layers;
  Layer *layers;

} Encoder; 

typedef struct{
  int channels;
  int height;
  int width;
  float *data;

} Image;
 
//forward function
float *encoder_forward(Image *input, Encoder *encoder){
    //int latent_size = encoder->latent_size;
   // float *latent_vector = malloc(latent_size * sizeof(float));
     
    float *current = input->data;
    float *next; 
    //iterating over the layers
    int current_is_owned = 0; 
    for(int i=0; i<encoder->num_layers; i++){
    
      next = malloc(encoder->layers[i].output_size * sizeof(float));
      if(next == NULL){
        if(current_is_owned) free(current);
        return NULL;
      }
      //loop for each multiplication operation
      for(int j=0; j< encoder->layers[i].output_size; j++){
        //loop where multiplcation and addition is happening
        float sum = 0;
          for(int k=0; k<encoder->layers[i].input_size;k++){
              sum += current[k] * encoder->layers[i].weights[encoder->layers[i].input_size*j+k];
        }
         sum += encoder->layers[i].bias[j];
         next[j] = sum; 
      }     
      if(current_is_owned)
        free(current); 

      current = next;
      current_is_owned = 1; 
        
    }
    //output = output @ layer 2 
    return next;
}
  //decoder block: 
    //input = latent vector 
    //output = reconstructed image (same dimension as the input image? maybe.)
int main(){

    printf("autoencoder\n");
  return 0;
}
