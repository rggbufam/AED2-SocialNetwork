/*
Author : Ruan Kotovich
Year : 2016
Licence : MIT
*/

#include "circularQueue.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct{
  int *array;
  int last;
  int first;
  int size;
  int itemCount;
}TQueueData;

static void f_printQueue(TQueue *queue){
  TQueueData *queueData = queue->data;

  printf("\n * Queue status - First : %d / Last : %d\n",queueData->first,queueData->last);
  for(int i=0;i<queueData->size;i++){
    printf("[%d]",queueData->array[i]);
  }

}

static void af_resizeQueue(TQueue *queue){
  TQueueData *queueData = (TQueueData*)queue->data;
  int newSize = queueData->size*2;
  int oldSize = queueData->size;
  int *oldArray = queueData->array;
  int *newArray = malloc(sizeof(int)*newSize);
  int i,k;

  if(queueData->first > queueData->last){

    for(i=queueData->first,k=0;i<queueData->size;i++,k++){
      newArray[k] = oldArray[i];
    }

    for(i=0;i<queueData->first;i++,k++){
      newArray[k] = oldArray[i];
    }

  }else{

    for(i=queueData->first,k=0;i<=queueData->last;i++,k++){
      newArray[k] = oldArray[i];
    }

  }

  queueData->first=0;
  queueData->last=oldSize-1;

  free(oldArray);

  queueData->array = newArray;
  queueData->size = newSize;
}


static void f_offerNumber(TQueue *queue,int num){
  TQueueData *data = (TQueueData*) queue->data;
  int newLast;

  if(data->size <= data->itemCount){
    af_resizeQueue(queue);
  }

  if(data->first>=0){

    newLast = (data->last + 1)  % data->size;

    data->array[newLast] = num;

    data->last = newLast;

  }else{
    data->array[++data->last] = num;
    data->first = data->last;
  }
  data->itemCount++;
}

static int f_peekNumber(TQueue* queue){
  TQueueData *data = queue->data;
  return data->array[data->first];
}

static int f_popNumber(TQueue *queue){
  TQueueData *data = queue->data;
  int newFirst;
  int retorno;

  if(data->itemCount==1){
    retorno = data->array[data->first];
    data->first = data->last = -1;
  }else{
    retorno = data->array[data->first];
    newFirst = (data->first+1) % data->size;
    data->first = newFirst;
  }
  data->itemCount--;
  return retorno;
}

static void f_clear(TQueue* queue){
  TQueueData *data = queue->data;
  data->first = data->last = -1;
  data->itemCount=0;
}

static short f_empty(TQueue *q){
  return ((TQueueData*)q->data)->itemCount == 0;
}

TQueue *new_Queue(int start){
  TQueue* queueP = (TQueue*)malloc(sizeof(TQueue));
  TQueueData *queueD =(TQueueData*)malloc(sizeof(TQueueData));
  queueP->data = queueD;
  queueD->array = malloc(sizeof(void*)*start);
  queueD->first = queueD->last = -1;
  queueD->itemCount = 0;
  queueD->size=10;
  queueP->offerNumber = f_offerNumber;
  queueP->popNumber = f_popNumber;
  queueP->peekNumber = f_peekNumber;
  queueP->printQueue = f_printQueue;
  queueP->empty = f_empty;
  queueP->clear = f_clear;
  return queueP;
}
