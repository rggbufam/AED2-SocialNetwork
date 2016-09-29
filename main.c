/*
Author : Ruan Kotovich
Year : 2016
Licence : MIT
*/

#include "graph.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char **argv){
  int vertexAmount = atoi(argv[1]);
  char ponderated = atoi(argv[2]);
  int variant = atoi(argv[3]);

  int vertex1, vertex2, pound;
  TQueue *queue = new_Queue(100);
  char *visiteds = malloc(vertexAmount*sizeof(char));
  int *path = malloc(vertexAmount*sizeof(int));

  TGraph *graph = new_graph(vertexAmount);

  if(ponderated){
    while(scanf("%d %d %d", &vertex1,&pound, &vertex2) == 3){
      graph->offerEdge(graph,vertex1,vertex2,pound);
    }
  }else{
    while(scanf("%d %d", &vertex1, &vertex2) == 2){
      graph->offerEdge(graph,vertex1,vertex2,1);
    }
  }

  graph->minimalCandle(graph,queue,path,visiteds,variant);

}
