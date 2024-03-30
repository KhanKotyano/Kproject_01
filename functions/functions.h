#ifndef _KFUNCTIONS_H
#define _KFUNCTIONS_H
//#include "f_stack.c"
//#include "f_common.c"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../rlib/raylib.h"
#define _NEAR_BLACK (Color){15, 15, 15, 255}
#define _MAX_INSTANCES 64
#define _TARGET_FPS 60
#define _MIN_ANIMATION_SPEED 1
#define _MAX_ANIMATION_SPEED 150
#define _ANIMATION_FPS_OFFSET 4
#define _VERYLOW_SPEED_ANIMATION (4*_ANIMATION_FPS_OFFSET)
#define _LOW_SPEED_ANIMATION (6*_ANIMATION_FPS_OFFSET)
#define _MIDDLE_SPEED_ANIMATION (9*_ANIMATION_FPS_OFFSET)
#define _MIDDLEPLUS_SPEED_ANIMATION (12*_ANIMATION_FPS_OFFSET)
#define _HIGHT_SPEED_ANIMATION (15*_ANIMATION_FPS_OFFSET)
#define _VERYHIGHT_SPEED_ANIMATION (20*_ANIMATION_FPS_OFFSET)

#define _EMPTY 0
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
typedef struct Animation2D {
  u8 animation_speed;
  u8 frame_counter;
  u8 max_frames;
  u8 curretnt_frame;
  Rectangle frame_rectangle;
  Texture2D *sprite_sheet;
} Animation2D;

typedef struct Instance {
  //Instance *ID;
  unsigned int ID;
  u8 active;
  Vector2 pos {0,0};
  Texture2D *sprite;
  float scale = 1;
  float angle = 0;
  Animation2D animation;
  //Instance *self_ptr;
  //u8 animation_speed;
  //u8 frame_counter;
  //u8 max_frames;
  //u8 curretnt_frame;
  //Rectangle frame_rectangle;
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

typedef struct IntArray{
  int *array;
  size_t used;
  size_t size;
} IntArray;

typedef struct InstanceArray{
  Instance *array;
  size_t used;
  size_t size;
} InstanceArray;


#ifndef KAPI
    #define KAPI       // Functions defined as 'extern' by default (implicit specifiers)
#endif



//Instances
/// @brief 
/// @param _position 
/// @param _sprite 
/// @param _inst_array 
/// @return Instance
//Instance CreateInstance(Vector2 _position, Texture2D *_sprite, Animation2D *_animation);

int PlayerIvent(Instance &self);
void AddInstance( Vector2 _position, InstanceArray *_inst_array, Texture2D *_sprite, Animation2D *_animation);
void UpdateInstances(InstanceArray *_inst_array);
void UpdateDrawInstances(InstanceArray *_inst_array);

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
//Draw
Animation2D CreateAnimation2D(Texture2D *_sprite_sheet, u8 _number_of_sprites, u8 _animation_speed);
Animation2D InheritAnimation2D(Animation2D *_sourse, u8 _animation_speed);
void DrawAndAnimate(Instance * _inst);
void GetFrameAnimation(Animation2D *_animation);
void DrawAnimation(Animation2D *_animation, Vector2 _pos);
//Arrays
bool RedoInstanceArray(InstanceArray *a);
//void CreateArrayInt(IntArray *a, size_t initialSize);
//Includes
#include "f_common.c"
#include "f_array.c"
#include "f_stack.c"
#include "f_instance.c"
#include "f_draw.c"

#endif