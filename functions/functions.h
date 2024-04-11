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
#define _MAX_INSTANCES 16
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
#define _INSTANCE_ID 1000000000

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
enum INST_TYPE {
  NOTHING = 0,
  PLAYER = 1,
  ENEMY = 2

};
enum P_TYPE{
  PT_VOID = 0,
  PT_CHAR = 1,
  PT_UCHAR = 2,
  PT_INT = 3,
  PT_UINT = 4,
  PT_FLOAT = 5,
  PT_DOUBLE = 6,

};
typedef struct custom_pointer {
  u8 pointer_type;
  union {
    void *p_void;
    char *p_char;
    unsigned char *p_uchar;
    int *p_int;
    unsigned int *p_uint;
    float *p_float;
    double *p_double;
  };

} custom_pointer;

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
  u32 ID;
  u8 exist;
  Vector2 pos ;
  Texture2D *sprite;
  float scale ;
  float angle ;
  Animation2D animation;
  void (*f_main)(Instance*);
  void (*f_draw)(Instance*);
  void (*f_drawGUI)(Instance*);
  //void (*f_main)(Instance*);
  //void (*f_main_draw)(Instance*);
  u16 type;
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
void DrawSelf(Instance *self);
void AnimateSelf(Instance *self);
//void PlayerIvent(Instance *self);
void AddInstance( Vector2 _position, InstanceArray *_inst_array, Texture2D *_sprite, Animation2D *_animation);
void UpdateInstances(InstanceArray *_inst_array);
void UpdateDrawInstances(InstanceArray *_inst_array);
//void AssignTypeFunctions(void(**_function_array)(Instance*), u16 _type);
//Common
char* FloatToString( float recast );
char* IntToString( int recast );
//char* ToStringInt( int recast , char *str);
//char* ToStringFloat( float recast , char *str);
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
int FindEmptyInstance(Instance *array, s32 _offset, s32 _max_lng);
int FindNotEmptyInstance(Instance *array, s32 _offset, s32 _max_lng);
//void CreateArrayInt(IntArray *a, size_t initialSize);
//Includes
#include "f_common.c"
#include "f_array.c"
#include "f_stack.c"
#include "f_draw.c"
#include "f_inst_step_ivent.c"
#include "f_inst_draw_ivent.c"
#include "f_instance.c"
//#include "f_UI.c"

#endif