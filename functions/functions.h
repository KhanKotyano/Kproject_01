#ifndef _KFUNCTIONS_H
#define _KFUNCTIONS_H
//#include "f_stack.c"
//#include "f_common.c"

#include <stdio.h>
#include <stdlib.h>
#include "../rlib/raylib.h"
#define _NEAR_BLACK (Color){15, 15, 15, 255}
#define _MAX_INSTANCES 32

#pragma region Variable Declaration
typedef signed char s8;
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef signed long s64;
typedef unsigned long u64;
typedef float f32;
typedef double f64;

typedef union {
	s8 s8;
	u8 u8;
	s16 s16;
	u16 u16;
	s32 s32;
	u32 u32;
	s64 s64;
	u64 u64;
	f32 f32;
	f64 f64;
} Var;
#pragma endregion

typedef struct Instance {
  u32 ID;
  bool active;
  Vector2 pos {0,0};
  Texture2D *sprite;
  u8 animation_speed;
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
Instance CreateInstance(Vector2 _position, Texture2D *_sprite);
int PlayerIvent(Instance &self);
void AddInstance( Vector2 _position, Instance *_inst_array, Texture2D *_sprite);
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