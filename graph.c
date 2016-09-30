/*
Author : Ruan Kotovich
Year : 2016
Licence : MIT
*/

#include "graph.h"
#include "stdlib.h"
#include "stdio.h"
#include "limits.h"

typedef struct tgraphData{
  int *matrix;
  int matrixLength;
}TGraphData;

static void f_offerEdge(TGraph* graph,int vertex1, int vertex2, int value){
  TGraphData *data = (TGraphData*) graph->data;
  data->matrix[data->matrixLength * vertex2 + vertex1] = data->matrix[data->matrixLength * vertex1 + vertex2] =  value;
}

static void f_removeEdge(TGraph* graph, int vertex1, int vertex2){
  TGraphData *data = (TGraphData*) graph->data;
  data->matrix[data->matrixLength * vertex1 + vertex2] = data->matrix[data->matrixLength * vertex2 + vertex1] = 0;
}

static int f_recoverEdge(TGraph* graph, int vertex1, int vertex2){
  TGraphData *data = (TGraphData*) graph->data;
  return data->matrix[data->matrixLength * vertex1 + vertex2] ;
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

static void f_printAdjacencyMatrix(TGraph* graph){
  TGraphData *data = graph->data;
  for(int i=0;i<data->matrixLength;i++){
    for(int j=i+1;j<data->matrixLength;j++){
      if(data->matrix[data->matrixLength * i + j]){
        printf("%d %d\n",i,j);
      }
    }
  }
}

static int* af_breadthfirstsearch(TGraphData* data, TQueue *pathQueue,char *visiteds,int *path,int start, int end){
  int current;
  //printf("\n BFS from %d to %d",start,end);
  for(int i=0;i<data->matrixLength;i++){
    visiteds[i] = 0;
  }

  path[start] = path[end] = -1;

  visiteds[start] = 1;

  pathQueue->offerNumber(pathQueue,start);

  while(!pathQueue->empty(pathQueue)){
    current = pathQueue->popNumber(pathQueue);

    if(current == end){
      //printf("\n\tEnd found");
      return path;

    }else{
      for(int i=0;i<data->matrixLength;i++){
        //printf("\n\t[%d %d]Found %d from %d",data->matrix[data->matrixLength * current + i],visiteds[i],i,current);
        if(data->matrix[data->matrixLength * current + i]? !visiteds[i] : 0){
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
  char *visiteds = malloc(data->matrixLength*sizeof(char));
  int *path = malloc(data->matrixLength*sizeof(int));
  int *field;

  field = af_breadthfirstsearch(data, new_Queue(10),visiteds, path, start, end);

  free(visiteds);

  return field;
}

static int* af_dijkstra(TGraphData* data, int* magnitude, int* path, char*visiteds,int start, int end){
  int current;
  int minimalValue,minimalPosition;
  int currentMagnitude;

  //printf("\n - Dijkstra from [%d] to [%d]",start,end);
  for(int i=0;i<data->matrixLength;i++){
    magnitude[i] = INT_MAX;
    visiteds[i] = 0;
  }

  path[start] = path[end] = -1;
  magnitude[start] = 0;

  current = start;

  while(current != -1){

    visiteds[current] = 1;

    if(current == end){
      return path;
    }else{

      for(int i=0;i<data->matrixLength;i++){
        currentMagnitude = data->matrix[data->matrixLength * current + i];
        if(currentMagnitude){
          //printf("\n\t - Encontrado [%d] a partir de [%d]",i,current);
          if(!visiteds[i]){
            currentMagnitude+= magnitude[current];
            if(magnitude[i] > currentMagnitude){
              //  printf(" e a magnitude foi trocada de %d para %d",magnitude[i],currentMagnitude);
              magnitude[i] = currentMagnitude;
              path[i] = current;
            }
          }//else{
            //        printf("(visitado)");
            //  }
          }
        }
      }

      minimalValue = INT_MAX;
      minimalPosition = -1;

      for(int i=0;i<data->matrixLength;i++){
        if(magnitude[i] < minimalValue && !visiteds[i]){
          minimalValue = magnitude[i];
          minimalPosition = i;
        }
      }
      //  printf("\n\t - Mínimo = %d",minimalPosition);
      current = minimalPosition;
    }
    return NULL;

  }

  static int* f_dijkstra(TGraph* graph, int start, int end){
    TGraphData* data = graph->data;
    int *magnitude = malloc(sizeof(int) * data->matrixLength);
    int *path = malloc(sizeof(int) * data->matrixLength);
    char *visiteds = malloc(sizeof(char) * data->matrixLength);
    int* retur = af_dijkstra(data, magnitude, path, visiteds, start, end);
    free(magnitude);
    free(visiteds);

    return retur;

  }

  static int* af_minimalChain(TGraph *graph,TQueue *queue,int *magnitude,int* edgeCount,int* path, char* visiteds){
    TGraphData *data = graph->data;
    int *gotPath;
    int currentVertex, currentPath;

    for(int i=0;i<data->matrixLength;i++){
      for(int j=i+1;j<data->matrixLength;j++){
        gotPath = af_breadthfirstsearch(data,queue,visiteds,path,i,j);
        //gotPath  = af_dijkstra(data, magnitude, path,visiteds, i, j);
        queue->clear(queue);
        //printf("\n Minimal path from %d to %d : ",i,j);
        if(gotPath){
          currentVertex = j;
          while(currentVertex != i){
            currentPath =  gotPath[currentVertex];
            edgeCount[data->matrixLength*currentVertex + currentPath]++;
            //printf("[%d]",currentVertex);
            currentVertex = currentPath;
          }
          //printf("[%d]",currentVertex);
        }
      }
    }
    return edgeCount;
  }

  static int af_getFirstUnvisited(TGraphData* data,char *visiteds){

    for(int i=0;i<data->matrixLength;i++){
      if(!visiteds[i]) return i;
    }

    return -1;
  }

  static void af_conexComponents(TGraphData* data, TQueue *pathQueue,char *visiteds){
    int current = 0;

    for(int i=0;i<data->matrixLength;i++){
      visiteds[i] = 0;
    }

    pathQueue->clear(pathQueue);

    current = af_getFirstUnvisited(data, visiteds);
    visiteds[current] = 1;
    printf("\n\nSource Target Neighbourhood");

    while(current!=-1){
      pathQueue->offerNumber(pathQueue,current);

      while(!pathQueue->empty(pathQueue)){
        current = pathQueue->popNumber(pathQueue);

        for(int i=0;i<data->matrixLength;i++){
          if(data->matrix[data->matrixLength * current + i]){
            if(current != i){
              printf("\n%d %d NH_%d",current,i,current);
            }
            if(!visiteds[i]){
              pathQueue->offerNumber(pathQueue,i);
              visiteds[i] = 1;
            }
          }
        }
      }
      
      printf("\n");
      
      current = af_getFirstUnvisited(data, visiteds);
      visiteds[current] = 1;
    }
  }

  static void f_minimalCandle(TGraph *graph, TQueue *queue,int *path,char *visiteds,int variant){
    TGraphData *data = graph->data;
    float totalSum,totalItems,average,distribution;
    int biggerI,biggerJ,biggerValue,actualValue,*edgeCount,vertexAmount,actualPosI,actualPosJ;
    int *magnitude = malloc(data->matrixLength*sizeof(int));

    vertexAmount = data->matrixLength;
    edgeCount = calloc(vertexAmount*vertexAmount,sizeof(int));

    do{
      totalSum=0.0f;
      totalItems=0;
      biggerI = biggerJ = biggerValue = -1;
      printf("\n========================================================");
      edgeCount = af_minimalChain(graph,queue,magnitude,edgeCount,path,visiteds);

      for(int i=0;i<vertexAmount;i++){
        for(int j=i+1;j<vertexAmount;j++){
          actualPosI = vertexAmount*i+j;
          actualPosJ = vertexAmount*j+i;

          actualValue = edgeCount[actualPosI]+edgeCount[actualPosJ];
          edgeCount[actualPosI]=edgeCount[actualPosJ] = 0;

          if(actualValue>0){
            if(actualValue>biggerValue){
              biggerValue = actualValue;
              biggerI = i;
              biggerJ = j;
            }
            printf("\n- Edge <%d,%d> : %d",i,j,actualValue);
            totalSum+=actualValue;
            totalItems++;
          }
        }
      }

      average = totalSum/totalItems;
      distribution = biggerValue-average;
      printf("\n\n\n Medidas : ");
      printf("\n - Média : %f",average);
      printf("\n - Mais repetido : <%d,%d> -> %dx",biggerI,biggerJ,biggerValue);
      printf("\n - Distância Superior : %f",distribution);
      graph->removeEdge(graph,biggerI,biggerJ);

    }while(distribution>variant);

    af_conexComponents(data, queue, visiteds);

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
    newo->printAdjacencyMatrix = f_printAdjacencyMatrix;
    newo->dijkstra = f_dijkstra;
    newo->minimalCandle = f_minimalCandle;

    return newo;
  }
