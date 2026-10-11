#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

TransformerModel *create_transformer_model(int num_layers, int d_model){
 
    TransformerModel *model = malloc(sizeof(TransformerModel)); 
    model->forwardCache = malloc(sizeof(ForwardCache));
    
    model->num_layers = num_layers;
    model->d_model = d_model;
    // assign the memory for the layers + cache on heap
    model->layers = malloc(num_layers * sizeof(TransformerLayer));
    model->forwardCache->layerCaches = calloc(num_layers, sizeof(LayerCache));
    // initialize the weights for all the layers 
    Transformer_initialize_weights(model);
    
    return model;
  }

int Transformer_forward(TransformerModel *model, Matrix *input){

    for(int i=0; i<model->num_layers; i++){
      single_head_attention_forward(input, &model->layers[i], &model->forwardCache->layerCaches[i], model->d_model, 1);

    }
    return 1; 
}
// MAIN FUNCTION
int main(){

  TransformerModel *model = create_transformer_model(3,4);
  Matrix input; 
  Matrix_alloc(&input, 5,4);
  Matrix_create_random(&input, 5,4);
  
  Transformer_forward(model, &input);
  printf("FORWARD DONE!!");
  Matrix_print(&model->forwardCache->layerCaches[0].out);
  return 0;
}
