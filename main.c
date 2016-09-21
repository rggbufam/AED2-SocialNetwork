#include "graph.h"
#include "stdio.h"
#include "stdlib.h"

int main(int argc, char **argv){
  int vertexAmount = atoi(argv[1]);
  char ponderated = atoi(argv[2]);
  int vertex1, vertex2, pound;
  int *path;

  FILE* bookshire = fopen(argv[3],"r+");
  TGraph *graph = new_graph(vertexAmount);

  fseek(bookshire,0,SEEK_SET);
  if(ponderated){
    while(fscanf(bookshire, "%d %d %d", &vertex1,&pound, &vertex2) == 3){
      graph->offerEdge(graph,vertex1,vertex2,pound);
    }
  }else{
    while(fscanf(bookshire, "%d %d", &vertex1, &vertex2) == 2){
      graph->offerEdge(graph,vertex1,vertex2,1);
    }
  }
  graph->printMatrix(graph);
  path = graph->breadthFirstSearch(graph,atoi(argv[4]),atoi(argv[5]));

  printf("\n");

  graph->printPath(graph,path,atoi(argv[4]),atoi(argv[5]));
  return 0;
}
