#ifndef KARRAY 
#define KARRAY
#include "functions.h"
#include <stdlib.h>

#ifndef _EMPTY
  #define _EMPTY 0
#endif
#ifndef _EMPTY_INT
  #define _EMPTY_INT -2
#endif
#pragma region Array Integer Implementation


void EmptyIntArray(IntArray *a, int _offset);
void InitArrayInt(IntArray *a, size_t initialSize);

void ArrayPushInt(IntArray *a, int element);
void ArrayEmptyIndexInt(IntArray *a, int _index);
void ArraySetIndexInt(IntArray *a, int _index, int _value);

int FindNotEmptyInt(int *array, s32 _offset, s32 _max_lng);
bool RedoIntArray(IntArray *a);

void freeArrayInt(IntArray *a);
void freeUsedAInt(IntArray *a) ;
#pragma endregion

#pragma region Inst Array
void EmptyInstanceArray(InstanceArray *a, int _offset);
void InitArrayInstance(InstanceArray *a, size_t initialSize) ;
void ArrayPushInstance(InstanceArray *a, Instance _instance) ;


void ArrayEmptyIndexInstance(InstanceArray *a, int _index);
void ArraySetIndexInstance(InstanceArray *a, int _index, Instance _instance);

int FindNotEmptyInstance(Instance *array, s32 _offset, s32 _max_lng);
int FindEmptyInstance(Instance *array, s32 _offset, s32 _max_lng);
bool RedoInstanceArray(InstanceArray *a);

void freeArrayInstance(InstanceArray *a) ;


void EmptyPtrArray(PointerArray *a, int _offset);
void InitArrayPtr(PointerArray *a, size_t initialSize) ;

void ArrayPushPtr(PointerArray *a, custom_pointer element) ;
void ArrayEmptyIndexPtr(PointerArray *a, int _index);
void ArraySetIndexPtr(PointerArray *a, int _index, custom_pointer _value);

int FindNotEmptyPtr(custom_pointer *array, s32 _offset, s32 _max_lng);
bool RedoPtrArray(PointerArray *a);

void freeArrayPtr(PointerArray *a) ;

#pragma endregion
#include "f_array.c"
#endif