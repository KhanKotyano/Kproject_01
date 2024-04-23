#ifndef _KFUNCTIONS_H
#define _KFUNCTIONS_H
//#include "UIC.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../rlib/raylib.h"
//#include "../functions_lib/AStar.h"
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
#define PIXEL_SIZE 32
#define TRUE 1
#define FALSE 0

#define MAX_ZOOM 5.0F
#define MIN_ZOOM 0.25F

#define DEBUG_MODE true
#define DEBUG_MODE_SHOW_GRID false
#define DEBUG_MODE_SHOW_SIZE true
#define MAX_INSTANCES_IN_CELL 64

/*#ifndef _CUSTOM_DEF
  #define _CUSTOM_DEF
  #define GLOBAL_LOCKON_CELL global_pointer_array[G_LOCK_ON_CELL].p_cell
  #define GLOBAL_SCREEN_W global_pointer_array[G_SCREEN_W].p_int
  #define GLOBAL_SCREEN_H global_pointer_array[G_SCREEN_H].p_int

  #define MAIN_GRID_CUR_POS main_grid.grid[cell_on_hover.grid_pos.y][cell_on_hover.grid_pos.x]
#endif*/

typedef int DEPTH_TYPE;
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
struct custom_pointer;
struct Instance;
struct Cell;

enum global {
  G_SCREEN_W,
  G_SCREEN_H,
  G_WORLDGRID_H,
  G_WORLDGRID_W,
  G_INSTARRAY,
  G_WORLDCAM,
  G_CURCELL,
  G_MOUSE_WORLD_POS,
  G_LOCK_ON_CELL,
  G_EMPTY_CELL, 
  G_MAIN_GRID
};

enum INST_TYPE {
  NOTHING = 0,
  SOLDER = 1,
  ENEMY = 2

};

enum VAR_TYPE{
  T_EMPTY = 0,
  T_CHAR = 1,
  T_UCHAR = 2,
  T_INT = 3,
  T_UINT = 4,
  T_LONG = 5,
  T_ULONG = 6,
  T_FLOAT = 7,
  T_DOUBLE = 8,
 
};
enum MOVE_TYPE {
  STATIC = 0,
  WALK = 1,
  SWIM = 2,
  FLY = 3,
  AMPHIBIOUS = 4,
  GROUND_AND_AIR = 5,
  AIR_AND_WATER = 6,
  ALL = 7
};
enum CELL_WALK_TYPE {
  NONE = 0,
  LAND = 1,
  SEA = 2,
  AIR = 3
};

typedef struct custom_variable{
  u8 var_type;
  union {
    char t_char;
    unsigned char t_uchar;
    short t_short;
    unsigned short t_ushort;
    int t_int;
    unsigned int t_uint;
    long t_long;
    unsigned long t_ulong;
    float t_float;
    double t_double;
  };
} custom_variable;

#pragma endregion
typedef struct GridVector2D {
  unsigned int x;
  unsigned int y;
}GridVector2D;

typedef struct Animation2D {
  u8 animation_speed;
  u8 frame_counter;
  u8 max_frames;
  u8 curretnt_frame;
  Color color;
  Rectangle frame_rectangle;
  Texture2D *sprite_sheet;
} Animation2D;

enum states {
  NOT_INITIALIZED = 0,
  INITIALIZED = 1,
  NOT_SELECTED = 2,
  SELECTED = 3,
};

typedef struct CustomInstVar {
  Cell *my_cell;
}CustomInstVar;

typedef struct Instance {
  u32 ID;
  s8 exist;
  u8 state;
  Vector2 pos ;
  GridVector2D cell_pos;
  DEPTH_TYPE depth;
  //Texture2D *static_sprite;
  float scale ;
  float angle ;
  Animation2D animation;
  CustomInstVar custom_var;
  void (*f_create)(Instance*, custom_pointer*);
  void (*f_main)(Instance*, custom_pointer*);
  void (*f_draw)(Instance*, custom_pointer*);
  void (*f_drawGUI)(Instance*, custom_pointer*);
  u16 type;
  u8 custom_count;
  void (*f_custom[16])(Instance*);
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

typedef struct UICLayer {


}UICLayer;

typedef struct CameraInstance2D { 
  Instance *target_instance;
  Vector2 target_pos;
  Camera2D *camera;
}CameraInstance;
typedef struct Terrain {
  u8 type;
  u8 move_cost;
}Terrain;
typedef struct NaturalProperties {
  Terrain *terrain;

} NaturalProperties;

typedef struct Grid2D { 
  unsigned int width;
  unsigned int height;
  unsigned int **grid;
}Grid2D;
typedef struct Cell{
  GridVector2D grid_pos;
  NaturalProperties nature;
  Animation2D animation;
  u8 exist;
  u32 ID;
  Instance *contaned_inst;
}Cell;
typedef struct CellGrid2D { 
  unsigned int width;
  unsigned int height;
  Cell **grid;
}CellGrid2D;
#ifndef KAPI
  #define KAPI
#endif
enum P_TYPE{
  PT_VOID = 0,
  PT_CHAR = 1,
  PT_UCHAR = 2,
  PT_INT = 3,
  PT_UINT = 4,
  PT_FLOAT = 5,
  PT_DOUBLE = 6,
  PT_CAMERA = 9,
  PT_INST_ARRAY = 10,
  PT_CELL = 11,
  PT_VECTOR2 = 12, 
  PT_CELL_GRID2D = 13,

};


//Instances
void DumpFunction(Instance *self);
void DrawSelf(Instance *self);
void AnimateSelf(Instance *self);
//void PlayerIvent(Instance *self);
//void AddInstance( Vector2 _position, InstanceArray *_inst_array, Texture2D *_sprite, Animation2D *_animation);
void UpdateInstances(InstanceArray *_inst_array, custom_pointer *global_pointer_array);
void UpdateDrawInstances(InstanceArray *_inst_array, custom_pointer *global_pointer_array);
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
    CameraInstance2D *p_camera;
    InstanceArray *p_inst_array;
    Cell *p_cell;
    Vector2 *p_vector2D;
    CellGrid2D *p_grid_cell2D;
  };

} custom_pointer;
typedef struct PointerArray {
  size_t used;
  size_t size;
  custom_pointer *array;
}PointerArray;


//#include "../functions_lib/AStar.c"
#include "f_common.c"
#include "f_array.c"
#include "f_stack.c"
#include "f_draw.c"
#include "UIC.c"
#include "f_inst_step_ivent.c"
#include "f_inst_draw_ivent.c"
#include "f_instance.c"

#endif