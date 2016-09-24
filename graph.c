#include "graph.h"
#include "circularQueue.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct tgraphData{
  int *matrix;
  int matrixLength;
}TGraphData;

static void f_offerEdge(TGraph* graph,int vertex1, int vertex2, int value){
  TGraphData *data = (TGraphData*) graph->data;
  data->matrix[data->matrixLength * vertex1 + vertex2] = data->matrix[data->matrixLength * vertex2 + vertex1] = value;
}

static void f_removeEdge(TGraph* graph, int vertex1, int vertex2){
  TGraphData *data = (TGraphData*) graph->data;
  data->matrix[data->matrixLength * vertex1 + vertex2] = data->matrix[data->matrixLength * vertex2 + vertex1] = 0;
}

static int f_recoverEdge(TGraph* graph, int vertex1, int vertex2){
  TGraphData *data = (TGraphData*) graph->data;
  return data->matrix[data->matrixLength * vertex1 + vertex2] ;//| data->matrix[data->matrixLength * vertex2 + vertex1];
}

static void f_printMatrix(TGraph* graph){
  TGraphData *data = graph->data;
  for(int i=0;i<data->matrixLength;i++){
    for(int j=0;j<data->matrixLength;j++){
      printf("[%d]",f_recoverEdge(graph, i ,j));
    }
    printf("\n");
  }
}

static int* af_breadthfirstsearch(TGraph* graph, int start, int end){
  TGraphData* data = graph->data;
  int *visiteds = calloc(data->matrixLength,sizeof(int));
  int *path = calloc(data->matrixLength,sizeof(int));
  TQueue *pathQueue = new_Queue();
  int current;

  for(int i=0;i<data->matrixLength;i++){
    visiteds[i] = 0;
    path[i] = -1;
  }

  visiteds[start] = 1;

  pathQueue->offerNumber(pathQueue,start);

  while(!pathQueue->empty(pathQueue)){

    current = pathQueue->popNumber(pathQueue);

    if(current == end){
      free(visiteds);
      return path;

    }else{

      for(int i=0;i<data->matrixLength;i++){
        if(f_recoverEdge(graph, current, i)? !visiteds[i] : 0){
          pathQueue->offerNumber(pathQueue,i);
          visiteds[i] = 1;
          path[i] = current;
        }
      }
    }
  }

  free(visiteds);
  free(path);

  return NULL;
}

static TDArray* f_breadthfirstsearch(TGraph *graph, int start, int end){
  TDArray *array = new_darray();
  int *path = af_breadthfirstsearch(graph, start, end);
  int iteration=0;
  int current = end;

  while(current != start){
    array->setDArrayItem(array,current,iteration);
    iteration++;
    current = path[current];
  }

  array->setDArrayItem(array,current,iteration);
  free(path);
  return array;
}

static int* af_brandBreadthFirstSearch(TGraph* graph, int start,int end){
  TDArray *array = f_breadthfirstsearch(graph, start, end);
  int limit = array->getUsed(array);
  int *path = calloc(limit,sizeof(int));

  for(int i=0;i<limit;i++){
    path[i] = array->getDArray(array)[i];
  }

  array->destroy(array);
  free(array);
  return path;
}

static void f_printPath(TGraph* graph, int start,int end){
  TDArray *array = f_breadthfirstsearch(graph, start, end);
  int limit = array->getUsed(array);

  printf("\n - path from %d to %d :\t ",start,end);
  for(int i=0;i<limit;i++){
    printf("[%d]",array->getDArray(array)[i]);
  }

  array->destroy(array);
  free(array);
}

static int** f_minimalChain(TGraph *graph){
  TGraphData* data = graph->data;
  int **chainMatrix = calloc(data->matrixLength * data->matrixLength, sizeof(int*));

  for(int i=0;i<data->matrixLength;i++){
    for(int j=i;j<data->matrixLength;j++){
      chainMatrix[data->matrixLength * i + j] = af_brandBreadthFirstSearch(graph, i,j);
    }
  }

  return chainMatrix;
}

static void f_printMinimalPaths(TGraph *graph){
  TGraphData* data = graph->data;
  for(int i=0;i<data->matrixLength;i++){
    for(int j=i;j<data->matrixLength;j++){
      f_printPath(graph, i, j);
    }
  }
}

TGraph *new_graph(int length){
  TGraph *newo = malloc(sizeof(TGraph));
  TGraphData *newoData = malloc(sizeof(TGraphData));

  newoData->matrix = calloc(length*length,sizeof(int));
  newoData->matrixLength = length;
  newo->data = newoData;

  newo->offerEdge = f_offerEdge;
  newo->recoverEdge = f_recoverEdge;
  newo->removeEdge = f_removeEdge;
  newo->breadthFirstSearch = f_breadthfirstsearch;
  newo->minimalChain = f_minimalChain;
  newo->printMinimalPaths = f_printMinimalPaths;
  newo->printMatrix = f_printMatrix;
  newo->printPath = f_printPath;

  return newo;
}
