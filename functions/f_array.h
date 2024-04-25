//#include "functions.h"
#include <stdlib.h>
//#include <time.h>
#ifndef _EMPTY_INSTANCE
  static Instance empty = {0};
  #define _EMPTY_INSTANCE empty
#endif
#ifndef _EMPTY_INT
  #define _EMPTY_INT -2
#endif
#pragma region Array Integer Implementation


void EmptyIntArray(IntArray *a, int _offset){
  for(int i = _offset;i< (int)a->size;i++){
    a->array[i] = _EMPTY_INT;
  }
};
void InitArrayInt(IntArray *a, size_t initialSize) {
  a->array = (int*)malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
  EmptyIntArray(a, 0);
};

void ArrayPushInt(IntArray *a, int element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (int*)realloc(a->array, a->size * sizeof(int));
    EmptyIntArray(a, a->used);
  }
  a->array[a->used++] = element;
}
void ArrayEmptyIndexInt(IntArray *a, int _index){
  a->array[_index] = _EMPTY_INT;
}
void ArraySetIndexInt(IntArray *a, int _index, int _value){
  a->array[_index] = _value;
}

int FindNotEmptyInt(int *array, s32 _offset, s32 _max_lng){
  for(s32 i = _offset;i < _max_lng;i++){
    if(array[i] != _EMPTY_INT){
      return i;
    }
  }
  return -1;
}
bool RedoIntArray(IntArray *a){
  int _counter = 0;
  for(s32 i = 0;i < (s32)a->used;i++){
    if(a->array[i] == _EMPTY_INT){
      _counter = i;
      int _empty_index = FindNotEmptyInt(a->array, i, a->used);
      if(_empty_index != -1){
        a->array[i] = a->array[_empty_index];
        a->array[_empty_index] = _EMPTY_INT;
      } else {
        a->used = (size_t)_counter;
        //a->used--;
        //array has space and it's been restructured
        return true;
      }
    }
  }
  //a->used = (size_t)_counter;
  //array is full
  return false;
}

void freeArrayInt(IntArray *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
};
void freeUsedAInt(IntArray *a) {
  ArrayEmptyIndexInt(a, 0);
  a->used = 0;
};
#pragma endregion

#pragma region Inst Array
void EmptyInstanceArray(InstanceArray *a, int _offset){
  for(int i = _offset;i< (int)a->size;i++){
    a->array[i] = _EMPTY_INSTANCE;
  }
}
void InitArrayInstance(InstanceArray *a, size_t initialSize) {
  a->array = (Instance*)malloc(initialSize * sizeof(Instance));
  a->used = 0;
  a->size = initialSize;
  EmptyInstanceArray(a, 0);
};
void ArrayPushInstance(InstanceArray *a, Instance _instance) {
  if (a->used == a->size) {
    //TODO: Maybe do it as separate check/function. Rn, it not optimal solution
    a->size *= 2;
    a->array = (Instance*)realloc(a->array, a->size * sizeof(Instance));
    EmptyInstanceArray(a, a->used);
    printf("New memory allocated to the instance array\n");
  }
  a->array[a->used++] = _instance;
  //a->array[a->used-1].ID = a->used;
}


void ArrayEmptyIndexInstance(InstanceArray *a, int _index){
  a->array[_index] = _EMPTY_INSTANCE;
}
void ArraySetIndexInstance(InstanceArray *a, int _index, Instance _instance){
  a->array[_index] = _instance;
}

int FindNotEmptyInstance(Instance *array, s32 _offset, s32 _max_lng){
  for(s32 i = _offset;i < _max_lng;i++){
    if(array[i].exist != _EMPTY){
      return i;
    }
  }
  return -1;
  
}
int FindEmptyInstance(Instance *array, s32 _offset, s32 _max_lng){
  for(s32 i = _offset;i < _max_lng;i++){
    if(array[i].exist == _EMPTY){
      return i;
    }
  }
  return -1;
}
bool RedoInstanceArray(InstanceArray *a){
  int _counter = 0;
  for(s32 i = 0;i < (s32)a->used;i++){
    if(a->array[i].exist == _EMPTY){
      _counter = i;
      int _empty_index = FindNotEmptyInstance(a->array, i, a->used);
      if(_empty_index != -1){
        a->array[i] = a->array[_empty_index];
        a->array[_empty_index] = _EMPTY_INSTANCE;
      } else {
        a->used = (size_t)_counter;
        //array has space and it's been restructured
        return true;
      }
    }
  }
  //a->used = (size_t)_counter;
  //array is full
  return false;
}

void freeArrayInstance(InstanceArray *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
};


void EmptyPtrArray(PointerArray *a, int _offset){
  for(int i = _offset;i< (int)a->size;i++){
    a->array[i].p_void = NULL;
    a->array[i].pointer_type = PT_VOID;
  }
};
void InitArrayPtr(PointerArray *a, size_t initialSize) {
  a->array = (custom_pointer*)malloc(initialSize * sizeof(custom_pointer));
  a->used = 0;
  a->size = initialSize;
  EmptyPtrArray(a, 0);
}

void ArrayPushPtr(PointerArray *a, custom_pointer element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (custom_pointer*)realloc(a->array, a->size * sizeof(custom_pointer));
    EmptyPtrArray(a, a->used);
  }
  a->array[a->used++] = element;
}
void ArrayEmptyIndexPtr(PointerArray *a, int _index){
  a->array[_index].p_void = NULL;
  a->array[_index].pointer_type = PT_VOID;
}
void ArraySetIndexPtr(PointerArray *a, int _index, custom_pointer _value){
  a->array[_index] = _value;
}

int FindNotEmptyPtr(custom_pointer *array, s32 _offset, s32 _max_lng){
  for(s32 i = _offset;i < _max_lng;i++){
    if(array[i].pointer_type != _EMPTY){
      return i;
    }
  }
  return -1;
}
bool RedoPtrArray(PointerArray *a){
  int _counter = 0;
  for(s32 i = 0;i < (s32)a->used;i++){
    if(a->array[i].pointer_type == _EMPTY){
      _counter = i;
      int _empty_index = FindNotEmptyPtr(a->array, i, a->used);
      if(_empty_index != -1){
        a->array[i] = a->array[_empty_index];
        a->array[_empty_index].pointer_type = _EMPTY;
      } else {
        a->used = (size_t)_counter;
        return true;
      }
    }
  }
  return false;
}

void freeArrayPtr(PointerArray *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
};

#pragma endregion


/*
typedef struct Array{
  void *array;
  size_t used;
  size_t size;
} Array;

void CreateArray(Array *a, size_t initialSize, size_t _esize) {
  a->array = malloc(initialSize * _esize);
  a->used = 0;
  a->size = initialSize;
}

void InsertArray(Array *a, int element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}
Array* insert_data(int t, void* s)
{
    Array * d = (Array*)malloc(sizeof(Array));
    d->size = sizeof(*s);
    d->array = s;

    return d;
}

void freeArray(Array *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}*/