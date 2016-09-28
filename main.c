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
  int vertex1, vertex2, pound;
  int *edgeCount;

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

  //graph->printMatrix(graph);
  edgeCount = graph->minimalChain(graph);
  for(int i=0;i<vertexAmount;i++){
    for(int j=i+1;j<vertexAmount;j++){
      printf("\n- Edge <%d,%d> : %d",i,j,edgeCount[vertexAmount*i+j]+edgeCount[vertexAmount*j+i]);
    }
  }
}
