#ifndef _KFUNCTIONS_H
#define _KFUNCTIONS_H
//#include "f_stack.c"
//#include "f_common.c"

#include <stdio.h>
#include <stdlib.h>
#include "../rlib/raylib.h"
#define _NEAR_BLACK (Color){15, 15, 15, 255}
#define _MAX_INSTANCES 64

typedef struct Instance {
  int ID;
  bool active;
  Vector2 pos {0,0};
  Texture2D *sprite;
  float scale = 1;
  float angle = 0;
}Instance;


typedef struct Instance3D {
  Vector3 pos;
  Texture *sprite;
  
}Instance3D;

struct stack{
    int maxsize;    // define max capacity of the stack
    int top;
    int *items;
}stack;
 
#ifndef KAPI
    #define KAPI       // Functions defined as 'extern' by default (implicit specifiers)
#endif



//Instances
/// @brief 
/// @param _position 
/// @param _sprite 
/// @param _inst_array 
/// @return Instance
Instance CreateInstance(Vector2 _position, Texture2D *_sprite, Instance *_inst_array);
int PlayerIvent(Instance &self);
void AddInstance(Instance *_inst, Instance *_inst_array);
void UpdateInstances(Instance *_inst_array);
void UpdateDrawInstances(Instance *_inst_array);
//Common
char* FloatToString( float recast );
char* IntToString( int recast );
//Stack
struct stack* newStack(int capacity);
int size(struct stack *pt);
int IsStackEmpty(struct stack *pt);
int isFull(struct stack *pt);
void push(struct stack *pt, int x);
int peek(struct stack *pt);
int pop(struct stack *pt);
//Includes
#include "f_common.c"
#include "f_stack.c"
#include "f_instance.c"
#endif