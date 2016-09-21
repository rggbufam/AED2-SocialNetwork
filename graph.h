#ifndef _SOCIAL_NETWORK_GRAPH_
#define _SOCIAL_NETWORK_GRAPH_

typedef struct tgraph TGraph;

typedef void(*FOfferEdge)(TGraph*,int,int,int);
typedef void(*FRemoveEdge)(TGraph*,int,int);
typedef int(*FRecoverEdge)(TGraph*,int,int);
typedef int*(*FBreadthFirstSearch)(TGraph*,int,int);
typedef void(*FPrintPath)(TGraph*,int*,int,int);
typedef void(*FPrintMatrix)(TGraph*);

typedef struct tgraph{
  void* data;
  FOfferEdge offerEdge;
  FRemoveEdge removeEdge;
  FRecoverEdge recoverEdge;
  FPrintMatrix printMatrix;
  FPrintPath printPath;
  FBreadthFirstSearch breadthFirstSearch;
}TGraph;

TGraph* new_graph(int);

#endif // _SOCIAL_NETWORK_GRAPH_
