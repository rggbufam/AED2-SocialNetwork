#include "darray.h"
#include "stdlib.h"
#include "math.h"

typedef struct{
  int *vector;
  int size;
  int used;
}TDArrayData;

static void af_resizeVector(TDArray* array, int referential){
  TDArrayData *data = array->data;
  int k = floor(log2(referential)) + 1;
  int newSize = (int)pow(2,k);
  int *newVector = calloc(newSize,sizeof(int));

  for(int i=0;i<data->size;i++){
    newVector[i] = data->vector[i];
  }

  free(data->vector);
  data->vector = newVector;
  data->size = newSize;

}

static void f_seTDArrayItem(TDArray* array, int item, int pos){
  TDArrayData *data = array->data;

  if(data->size <= pos){
    af_resizeVector(array, pos);
  }

  data->vector[pos] = item;
  data->used=pos+1;
}

static int f_geTDArrayItem(TDArray* array, int pos){
  TDArrayData *data = array->data;
  return data->vector[pos];
}

static int f_arraySize(TDArray* array){
  return ((TDArrayData*)array->data)->size;
}

static int f_getUsed(TDArray * array){
  return ((TDArrayData*)array->data)->used;
}

static int* f_getDArray(TDArray *array){
  return ((TDArrayData*)array->data)->vector;
}

static void f_destroy(TDArray *array){
  free(((TDArrayData*)array->data)->vector);
}

TDArray *new_darray(){
  TDArray *arr = malloc(sizeof(TDArray));
  TDArrayData *data = malloc(sizeof(TDArrayData));
  arr->data = data;
  data->size = 2;
  data->used = 0;
  data->vector = calloc(data->size,sizeof(void*));

  arr->getDArrayItem = f_geTDArrayItem;
  arr->getDArraySize = f_arraySize;
  arr->setDArrayItem = f_seTDArrayItem;
  arr->destroy = f_destroy;
  arr->getDArray = f_getDArray;
  arr->getUsed = f_getUsed;

  return arr;
}
