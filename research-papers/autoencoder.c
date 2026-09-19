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
    //NULL checks 
    if(input == NULL || encoder == NULL) return NULL;

    //variable declarations
    float *current = input->data;
    float *next; 
    int current_is_owned = 0; 

    //iterating over 1 layer at a time
    for(int i=0; i<encoder->num_layers; i++){
    
      next = malloc(encoder->layers[i].output_size * sizeof(float));
      if(next == NULL){
          if(current_is_owned) free(current);
            return NULL;
      }
      //loop for each multiplication operation
      for(int j=0; j< encoder->layers[i].output_size; j++){
        //loop where multiplcation and addition is happening
        float sum = 0.0f;
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

int main(void) {
    printf("autoencoder encoder test\n");

    // 2x2 grayscale image: 4 input values
    float pixels[] = {
        2.0f, 2.0f,
        3.0f, 4.0f
    };

    Image input = {
        .channels = 1,
        .height = 2,
        .width = 2,
        .data = pixels
    };

    // Layer 0: 4 inputs -> 3 outputs (weights are 3x4)
    float weights0[] = {
        0.1f, 0.2f, 0.3f, 0.4f,
        0.5f, 0.6f, 0.7f, 0.8f,
        0.9f, 1.0f, 1.1f, 1.2f
    };
    float bias0[] = {0.0f, 0.0f, 0.0f};

    // Layer 1: 3 inputs -> 2 outputs (weights are 2x3)
    float weights1[] = {
        0.1f, 0.2f, 0.3f,
        0.4f, 0.5f, 0.6f
    };
    float bias1[] = {0.0f, 0.0f};

    Layer layers[] = {
        {
            .input_size = 4,
            .output_size = 3,
            .weights = weights0,
            .bias = bias0
        },
        {
            .input_size = 3,
            .output_size = 2,
            .weights = weights1,
            .bias = bias1
        }
    };

    Encoder encoder = {
        .latent_size = 2,
        .num_layers = 2,
        .layers = layers
    };

    float *latent = encoder_forward(&input, &encoder);

    if (latent == NULL) {
        fprintf(stderr, "encoder_forward failed\n");
        return 1;
    }

    printf("Latent vector: ");
    for (int i = 0; i < encoder.latent_size; i++) {
        printf("%.3f ", latent[i]);
    }
    printf("\n");

    free(latent);  // encoder_forward allocates the returned vector
    return 0;
}
