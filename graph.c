#include "graph.h"
#include "circularQueue.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct tgraphData{
  int *matrix;
  int matrixLength;
}TGraphData;

/*
0 1 2 3 4
0 |A|B|C|D|E|
1 |F|G|H|I|J|
2 |K|L|M|N|O|
3 |P|Q|R|S|T|
4 |U|V|W|X|Y|

m[3,2] = v[16] = v[5*3 + 1];
m[3,0] = v[5*3 + 0] = v[15];
m[2,4] = v[5*2 + 4] = v[14];
m[0,4] = v[5*0 + 4] = v[4];
*/

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

static void f_printPath(TGraph* graph, int* path,int start,int end){
  int current = end;

  printf("\n Path from %d to %d: ",start,end);
  while(current != start){
    printf("[%d]",current);
    current = path[current];
  }
  printf("[%d]",current);
}

static int* f_breadthfirstsearch(TGraph* graph, int start, int end){
  TGraphData* data = graph->data;
  int *visiteds = calloc(data->matrixLength,sizeof(int));
  int *path = calloc(data->matrixLength,sizeof(int));
  TQueue *pathQueue = new_Queue();
  int current;

  for(int i=0;i<data->matrixLength;i++){
    visiteds[i] = 0;
    path[i] = 0;
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
          //printf("\nFound vertex [%d] from [%d]",i,current);
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
  newo->printMatrix = f_printMatrix;
  newo->printPath = f_printPath;

  return newo;
}
