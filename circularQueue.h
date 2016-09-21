#ifndef _SOCIAL_NETWORK_CIRCULARQUEUE_
#define _SOCIAL_NETWORK_CIRCULARQUEUE_

typedef struct typeQueue TQueue;

typedef void(*FOfferNumber)(TQueue*,int);
typedef int(*FPeekNumber)(TQueue*);
typedef int(*FPopNumber)(TQueue*);
typedef void (*FPrintQueue)(TQueue*);
typedef short(*FEmpty)(TQueue*);

typedef struct typeQueue{
  void* data;
  FOfferNumber offerNumber;
  FPeekNumber peekNumber;
  FPopNumber popNumber;
  FPrintQueue printQueue;
  FEmpty empty;
}TQueue;

TQueue *new_Queue();

#endif ///_SOCIAL_NETWORK_CIRCULARQUEUE_
