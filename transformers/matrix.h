#ifndef MATRIX_H
#define MATRIX_H

//defining a Matrix struct 
typedef struct{
  int rows;
  int cols;
  float *data;

} Matrix;

typedef struct{
  Matrix Q_W;
  Matrix K_W;
  Matrix V_W;

} AttentionWeights;

typedef struct{
  AttentionWeights attention;
} TransformerLayer;
typedef struct{
  Matrix out;

} LayerCache;

typedef struct{
  int num_layers;
  LayerCache *layerCaches;

} ForwardCache;
// functions

typedef struct{
  int num_layers;
  int d_model;
  TransformerLayer *layers;
  ForwardCache *forwardCache;

} TransformerModel;

int Transformer_initialize_weights(TransformerModel *model);

Matrix *single_head_attention_forward(Matrix *input, TransformerLayer *layer, LayerCache *cache, int d_model, int residual_connection);

int Matrix_create_random(Matrix *M, int rows, int cols);
int Matrix_create_ones(Matrix *M, int rows, int cols);
int Matrix_alloc(Matrix *M, int rows, int cols);
int Matrix_print(Matrix *M);
#endif
