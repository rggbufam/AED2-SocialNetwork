/*
Author : Ruan Kotovich
Year : 2016
Licence : MIT
*/

#ifndef _XYAH_DARRAY_H_
#define _XYAH_DARRAY_H_

typedef struct dArray TDArray;

typedef int (*FGetDArrayItem)(TDArray*,int);
typedef void (*FSetDArrayItem)(TDArray*,int,int);
typedef int (*FGetDArraySize)(TDArray*);
typedef int* (*FGetArray)(TDArray*);
typedef int (*FGetUsed)(TDArray*);
typedef void (*FDestroy)(TDArray*);


 struct dArray{
  void *data;
  FGetDArrayItem getDArrayItem;
  FSetDArrayItem setDArrayItem;
  FGetDArraySize getDArraySize;
  FGetArray getDArray;
  FGetUsed getUsed;
  FDestroy destroy;
};

TDArray *new_darray();

#endif
