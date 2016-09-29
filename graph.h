/*
Author : Ruan Kotovich
Year : 2016
Licence : MIT
*/

#ifndef _SOCIAL_NETWORK_GRAPH_
#define _SOCIAL_NETWORK_GRAPH_
#include "circularQueue.h"

typedef struct tgraph TGraph;

typedef void(*FOfferEdge)(TGraph*,int,int,int);
typedef void(*FRemoveEdge)(TGraph*,int,int);
typedef int(*FRecoverEdge)(TGraph*,int,int);
typedef int*(*FMininamChain)(TGraph*,TQueue*,int*,int*,char*);
typedef int*(*FBreadthFirstSearch)(TGraph*,int,int);
typedef int*(*FDijkstra)(TGraph*,int,int);
typedef void(*FPrintMatrix)(TGraph*);
typedef void(*FPrintAdjacencyMatrix)(TGraph*);
typedef void(*FMinimalCandle)(TGraph*, TQueue*, int*,char*,int);

typedef struct tgraph{
  void* data;
  FOfferEdge offerEdge;
  FRemoveEdge removeEdge;
  FRecoverEdge recoverEdge;
  FPrintMatrix printMatrix;
  FPrintAdjacencyMatrix printAdjacencyMatrix;
  FBreadthFirstSearch breadthFirstSearch;
  FDijkstra dijkstra;
  FMininamChain minimalChain;
  FMinimalCandle minimalCandle;
}TGraph;

TGraph* new_graph(int);

#endif // _SOCIAL_NETWORK_GRAPH_
