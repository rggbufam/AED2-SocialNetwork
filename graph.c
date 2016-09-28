/*
Author : Ruan Kotovich
Year : 2016
Licence : MIT
*/

#include "graph.h"
#include "circularQueue.h"
#include "stdlib.h"
#include "stdio.h"
#include "limits.h"

typedef struct tgraphData{
  int *matrix;
  int matrixLength;
}TGraphData;

static void f_offerEdge(TGraph* graph,int vertex1, int vertex2, int value){
  TGraphData *data = (TGraphData*) graph->data;
  data->matrix[data->matrixLength * vertex2 + vertex1] =  value;
}

static void f_removeEdge(TGraph* graph, int vertex1, int vertex2){
  TGraphData *data = (TGraphData*) graph->data;
  data->matrix[data->matrixLength * vertex2 + vertex1] = 0;
}

static int f_recoverEdge(TGraph* graph, int vertex1, int vertex2){
  TGraphData *data = (TGraphData*) graph->data;
  return data->matrix[data->matrixLength * vertex2 + vertex1] ;
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

static int af_getMinorMagnitude(TGraph* graph, int* magnitude, char* visiteds){
  TGraphData* data = graph->data;
  int minor = -1;

  for(int i=0;i<data->matrixLength;i++){
    if(magnitude[i] >= 0 && !visiteds[i] && (minor >=0? magnitude[i] < magnitude[minor]: 1)){
      minor = i;
    }
  }
  return minor;
}

static int* af_dijkstra(TGraph* graph, int *magnitude, char *visiteds,int *path,int start, int end){
  TGraphData* data = graph->data;

  int current,currentMagnitude;

  for(int i=0;i<data->matrixLength;i++){
    visiteds[i] = 0;
    path[i] = -1;
    magnitude[i] = INT_MAX;
  }

  visiteds[start] = 1;
  magnitude[start] = 0;

  current = start;

  while(current>=0){
    visiteds[current] = 1;
    if(current == end){
      return path;
    }else{

      for(int i=0;i<data->matrixLength;i++){
        currentMagnitude = f_recoverEdge(graph, current, i);

        if(currentMagnitude != 0 && !visiteds[i]){
          currentMagnitude+=magnitude[current];
          if(currentMagnitude < magnitude[i]){
            magnitude[i] = currentMagnitude;
            path[i] = current;
          }
        }
      }
    }
    current = af_getMinorMagnitude(graph, magnitude, visiteds);
  }

  return NULL;
}

static int *f_dijkstra(TGraph *graph, int start, int end){

  TGraphData* data = graph->data;
  char *visiteds = calloc(data->matrixLength,sizeof(char));
  int *magnitude = calloc(data->matrixLength,sizeof(int));
  int *path = calloc(data->matrixLength,sizeof(int));

  af_dijkstra(graph, magnitude,visiteds, path, start, end);

  free(magnitude);
  free(visiteds);

  return path;
}

static int* af_breadthfirstsearch(TGraph* graph, TQueue *pathQueue,char *visiteds,int *path,int start, int end){
  TGraphData* data = graph->data;
  int current;

  for(int i=0;i<data->matrixLength;i++){
    visiteds[i] = 0;
    //path[i] = -1;
  }
  path[start] = path[end] = -1;

  visiteds[start] = 1;

  pathQueue->offerNumber(pathQueue,start);

  while(!pathQueue->empty(pathQueue)){
    current = pathQueue->popNumber(pathQueue);

    if(current == end){
      return path;

    }else{
      for(int i=0;i<data->matrixLength;i++){
        if(f_recoverEdge(graph, current, i)? !visiteds[i] : 0){
          //printf("\n[%d]->[%d]",i,current);
          pathQueue->offerNumber(pathQueue,i);
          visiteds[i] = 1;
          path[i] = current;
        }

      }
    }
  }
  return NULL;
}

static int *f_breadthfirstsearch(TGraph *graph, int start, int end){
  TGraphData* data = graph->data;
  char *visiteds = calloc(data->matrixLength,sizeof(char));
  int *path = calloc(data->matrixLength,sizeof(int));
  int *field;

  field = af_breadthfirstsearch(graph, new_Queue(),visiteds, path, start, end);

  free(visiteds);

  return field;
}

static int* f_minimalChain(TGraph *graph){
  TGraphData *data = graph->data;
  TQueue *queue = new_Queue();
  char *visiteds = calloc(data->matrixLength,sizeof(char));
  int *path = calloc(data->matrixLength,sizeof(int));
  int *edgeCount = calloc(data->matrixLength*data->matrixLength,sizeof(int));
  int *gotPath;
  int currentVertex, currentPath;

  for(int i=0;i<data->matrixLength;i++){
    for(int j=i+1;j<data->matrixLength;j++){
      gotPath = af_breadthfirstsearch(graph,queue,visiteds,path,i,j);
      queue->clear(queue);
      if(gotPath){
        printf("\n Minimal path from %d to %d : ",i,j);
        currentVertex = j;
        while(currentVertex != i){
          currentPath =  gotPath[currentVertex];
          edgeCount[data->matrixLength*currentVertex + currentPath]++;
          printf("[%d]",currentVertex);
          currentVertex = currentPath;
        }
        printf("[%d]",currentVertex);
      }
    }
  }

  return edgeCount;
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
  newo->printMatrix = f_printMatrix;
  newo->dijkstra = f_dijkstra;

  return newo;
}
