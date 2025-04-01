//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "rlib/raylib.h"
#include "rlib/raymath.h"
#include "rlib/rlgl.h"
#define ABS _abs64
#define or ||
#define and &&
#include "functions/functions.h"






const int screenWidth = 1280;
const int screenHeight = 720;
unsigned int WorldGridHeight = 10;
unsigned int WorldGridWidth = 20;
Camera2D camera = { 0 };
//Camera3D camera_3d = { 0 };
InstanceArray inst_array;
IntArray creation_inst_array = { 0 };
Cell cell_on_hover = { 0 }; 
Cell prev_on_hover = { 0 };
Cell lock_on_cell  = { 0 };
Cell empty_lockon_cell = { 0 };
Vector2 mouse_world_pos = { 0 };
PointerArray g_pt_array = { 0 };


#ifndef _CUSTOM_DEF
  #define _CUSTOM_DEF
  #define GLOBAL_PTR_ARRAY g_pt_array.array

  #define GLOBAL_LOCKON_CELL GLOBAL_PTR_ARRAY[G_LOCK_ON_CELL].p_cell
  #define GLOBAL_SCREEN_W GLOBAL_PTR_ARRAY[G_SCREEN_W].p_int
  #define GLOBAL_SCREEN_H GLOBAL_PTR_ARRAY[G_SCREEN_H].p_int
  #define GLOBAL_CAMERA GLOBAL_PTR_ARRAY[G_WORLDCAM].p_camera
  
  #define GLOBAL_CURRENT_CAMERA GLOBAL_PTR_ARRAY[G_WORLDCAM].p_camera->camera
  #define MAIN_GRID_CUR_POS main_grid.grid[cell_on_hover.grid_pos.y][cell_on_hover.grid_pos.x]


#endif




#define MAX_NEIGHBORS 4

typedef struct ASNode {
  GridVector2D pos;
  int F;
  int H;
  int G;
  u8 can_move;
  int parent_index;
  int border_nodes_size;
  int border_nodes_index[MAX_NEIGHBORS];
} ASNode;
typedef struct NodeArray {
  unsigned int total_size;
  unsigned int used_size;
  ASNode *array[];
}NodeArray;
typedef struct NodeIndexArray {
  unsigned int total_size;
  unsigned int used_size;
  int *array;
}NodeIndexArray;
typedef struct ASPath {
  IntArray open;
  IntArray closed;
  ASNode *node_map;
  IntArray final_path;
  int *priority_list;
  int *g_list;
  int *h_list;
  unsigned int max_w;
  unsigned int max_h;
}ASPath;
void OpenNode(NodeArray *open_node, ASNode *current_node){
  (open_node->array)[open_node->used_size++] = current_node;
};
void OpenIndexNode(IntArray *open_node, int curr_index){
  open_node->array[open_node->used++] = curr_index;
};
unsigned int GetMaxFCost(NodeArray *node_str){
  //node_str->array;
  int hight_index = 0;
  for(unsigned int i = 0;i < node_str->used_size;i++){
    if((node_str->array[i])->F >= (node_str->array[hight_index])->F){
      hight_index = i;
    }
  }
  return hight_index;
};
unsigned int GetMaxFCostIndex(IntArray *node_str, ASNode *path_array){
  int return_val;
  unsigned int hight_index = 0;
  int prev_max_val = path_array[node_str->array[hight_index]].F;
  for(unsigned int i = 0;i < node_str->used;i++){
    if(path_array[node_str->array[i]].F < prev_max_val){
      hight_index = i;
    }
  }
  return_val = (int)(node_str->array[hight_index]);
  ArrayEmptyIndexInt(node_str, hight_index);
  return return_val;
};
unsigned int GetMinValIndexArray(int *array, int *array2,unsigned int array_size){
  int return_val = INT_MIN;
  unsigned int min_index = 0;
  unsigned int i;
  for(i = 0;i<array_size;i++){
    //printf("val[%u]:%d\n", i,array[array2[i]]);
    if(array[array2[i]] < array[array2[min_index]]){min_index = i;}
  }
  //printf("min_val[%u]:%d\n",min_index,array[array2[min_index]]);
  return_val = (int)(array2[min_index]);
  array2[min_index] = _EMPTY_INT;
  return return_val;
}
bool IsIndexInArray(IntArray *array_str, int index){
  for(size_t i = 0;i < array_str->used;i++){
    if (array_str->array[i] == index) {
      return true;
    }
  }
  return false;
};
void CreateASNode(CellGrid2D *from_grid, ASNode **ASNode_array){
  *ASNode_array = (ASNode *)malloc(sizeof(ASNode) * (from_grid->height * from_grid->width));
  u32 cur_index = 0;
  u32 total_height = from_grid->height;
  u32 total_width = from_grid->width;
  for(u32 y = 0;y<total_height;y++){
    for(u32 x = 0;x<total_width;x++){
      cur_index = x + (y * (total_width));
      (*ASNode_array)[cur_index].can_move = from_grid->grid[y][x].exist;
      (*ASNode_array)[cur_index].G = (int)(from_grid->grid[y][x].nature.terrain->move_cost);
      (*ASNode_array)[cur_index].H = 0;
      (*ASNode_array)[cur_index].F = 0;
      (*ASNode_array)[cur_index].border_nodes_size = 0;
      (*ASNode_array)[cur_index].pos = (GridVector2D){.x = x,.y = y};
      // y0 x0 tw:6, th:4
      // y-1 = -1; no
      // x-1 = -1; no
      // y+1 = 1; yes; x(0) + ((y+1(1))*(tw(6)) = 06
      // x+1 = 1; yes; x(1) + ((y(0))*(tw(6)) = 01
      //if((*ASNode_array)[cur_index].can_move){
        if(y != 0){ 
          (*ASNode_array)[cur_index].border_nodes_index[(*ASNode_array)[cur_index].border_nodes_size++] = (x) + ((y-1) * (total_width));
        }
        if(x != 0){
          (*ASNode_array)[cur_index].border_nodes_index[(*ASNode_array)[cur_index].border_nodes_size++] = (x-1) + (y * (total_width));
        }
        if (y+1 < total_height){
          (*ASNode_array)[cur_index].border_nodes_index[(*ASNode_array)[cur_index].border_nodes_size++] = (x) + ((y+1) * (total_width));
        }
        if (x+1 < total_width){
          (*ASNode_array)[cur_index].border_nodes_index[(*ASNode_array)[cur_index].border_nodes_size++] = (x+1) + (y * (total_width));
        }
      //}
      #if false
        printf("y:%u x:%u Path index: %u ", y, x, cur_index);
        for(u32 j =0; j < (*ASNode_array)[cur_index].border_nodes_size; j++){
          printf("n[%u]:%u ", j, (*ASNode_array)[cur_index].border_nodes_index[j]);
        }
        printf("\n");
      #endif
    }
  }
}
int GridDistance(GridVector2D a, GridVector2D b){
  return (int)(abs(a.x - b.x) + abs(a.y - b.y));
}

void FindPathDi(ASPath *Path, GridVector2D from_node, GridVector2D target_node){
  unsigned int max_index = Path->max_h * Path->max_w;
  unsigned int from_index = (from_node.x + (from_node.y * Path->max_w));
  unsigned int target_index = (target_node.x + (target_node.y * Path->max_w));
  IntArray *open = &Path->open;
  IntArray *closed = &Path->closed;
  IntArray *final_path = &Path->final_path;
  if(Path->node_map[target_index].can_move){
    ArrayPushInt(open, from_index );
    int cur_border_index;
    #if DEBUG_MODE
      printf("START DICK \n");
    #endif
    int iteration = 0;
    int cost_so_far = 0;
    int new_cost = 0;
    unsigned int current_index = 0;
    for(int i = 0; i < max_index;i++){
      Path->node_map[i].H = GridDistance(Path->node_map[i].pos, Path->node_map[target_index].pos);
      Path->h_list[i] = Path->node_map[i].H;
      Path->g_list[i] = Path->node_map[i].G;
      Path->node_map[i].F = Path->node_map[i].H + Path->node_map[i].G;
      Path->priority_list[i] = Path->node_map[i].F;
      //printf("node map f: %d\n", Path->node_map[i].F);
    }
    current_index = from_index;
    while(open->used){
      iteration++;
      //current_index = GetMaxFCostIndex(open, Path->node_map);//index2D of path_array
      
      #if DEBUG_MODE
        printf("iteration:%d curr_index:%u\n", iteration, current_index);
      #endif
      if(current_index == target_index){
        #if DEBUG_MODE
          printf("path exist: cur_index:%u || target_index:%u \n", current_index, target_index);
        #endif
        
        while(current_index != from_index ){
          #if DEBUG_MODE
            printf("current path index: %u\n", current_index);
          #endif
          ArrayPushInt(final_path,current_index);
          current_index = Path->node_map[current_index].parent_index;
        }
        #if DEBUG_MODE
          printf("total path lenght: %llu\n", final_path->used);
        #endif
        RedoIntArray(open); //Shift quque
        return;
      }
      
      for(int i = 0;i < Path->node_map[current_index].border_nodes_size;i++){
        cur_border_index = Path->node_map[current_index].border_nodes_index[i];
        if(  !(Path->node_map[cur_border_index].can_move) or IsIndexInArray(closed, cur_border_index) ){ //
          continue;
        } 
        new_cost = abs(Path->g_list[current_index] - ((( Path->h_list[current_index] - Path->h_list[cur_border_index])) * Path->g_list[cur_border_index])); 
        if(new_cost < Path->priority_list[current_index] or !IsIndexInArray(open, cur_border_index)){ //
          Path->node_map[cur_border_index].parent_index = current_index;
          Path->g_list[cur_border_index] = new_cost + Path->g_list[cur_border_index];
          Path->priority_list[cur_border_index] = Path->g_list[cur_border_index];// + Path->h_list[cur_border_index];
          if(!IsIndexInArray(open, cur_border_index )){ //and !IsIndexInArray(closed, cur_border_index)
            ArrayPushInt(open, cur_border_index);
          }
        }
        
      }
      /*

      */
     
      ArrayPushInt(closed, current_index);
      RedoIntArray(open);
      current_index = GetMinValIndexArray(Path->priority_list, open->array,open->used);
      //RedoIntArray(open);
      
    }
  }
}

void CreatePath(ASPath *path, CellGrid2D *main_grid){
  CreateASNode(main_grid, &path->node_map);
  InitArrayInt(&path->open, (size_t)(sizeof(int ) * (main_grid->width *main_grid->height)));
  InitArrayInt(&path->closed, (size_t)(sizeof(int ) * (main_grid->width *main_grid->height)));
  InitArrayInt(&path->final_path, (size_t)(sizeof(int ) * (main_grid->width *main_grid->height)));
  path->priority_list = (int *)malloc(sizeof(int) * (main_grid->width *main_grid->height));
  path->g_list = (int *)malloc(sizeof(int) * (main_grid->width *main_grid->height));
  path->h_list = (int *)malloc(sizeof(int) * (main_grid->width *main_grid->height));
  path->max_h = main_grid->height;
  path->max_w = main_grid->width;
}
/*void FindPathASTAR(ASPath *Path, GridVector2D from_node, GridVector2D target_node){
  unsigned int max_index = Path->max_h * Path->max_w;
  unsigned int from_index = (from_node.x + (from_node.y * Path->max_w));
  unsigned int target_index = (target_node.x + (target_node.y * Path->max_w));
  IntArray *open = &Path->open;
  IntArray *closed = &Path->closed;
  IntArray *final_path = &Path->final_path;
  if(Path->node_map[target_index].can_move){
    ArrayPushInt(open, from_index );
    int cur_border_index;
    #if DEBUG_MODE
      printf("START ASTAR \n");
    #endif
    int iteration = 0;
    int cost_so_far = 0;
    unsigned int current_index = 0;
    for(int i = 0; i < max_index;i++){
      Path->priority_list[i] = Path->node_map[i].F;
      // Path->priority_list[i] = Path->node_map[i].F;
    }
    
    while(open->used){
      iteration++;
      //current_index = GetMaxFCostIndex(open, Path->node_map);//index2D of path_array
      current_index = GetMinValIndexArray(Path->priority_list, open->array,open->used);
      RedoIntArray(open);
      ArrayPushInt(closed, current_index);
      #if DEBUG_MODE
        printf("iteration:%d curr_index:%u\n", iteration, current_index);
      #endif
      if(current_index == target_index){
        #if DEBUG_MODE
          printf("path exist: cur_index:%u || target_index:%u \n", current_index, target_index);
        #endif
        
        while(current_index != from_index ){
          #if DEBUG_MODE
            printf("current path index: %u\n", current_index);
          #endif
          ArrayPushInt(final_path,current_index);
          current_index = Path->node_map[current_index].parent_index;
        }
        #if DEBUG_MODE
          printf("total path lenght: %llu\n", final_path->used);
        #endif
        RedoIntArray(open); //Shift quque
        return;
      }
      int priority = 0;
      int starting_prior;
      for(int i = 0;i < Path->node_map[current_index].border_nodes_size;i++){
        cur_border_index = Path->node_map[current_index].border_nodes_index[i];
        if( IsIndexInArray(closed, cur_border_index) or !(Path->node_map[cur_border_index].can_move) ){
          continue;
        } 
        starting_prior = Path->priority_list[cur_border_index];
        priority= starting_prior;
        
        //priority += (IsThisCloseGrid( Path->node_map[cur_border_index].pos , Path->node_map[target_index].pos)); 
        //priority -= (IsThisCloseGrid( Path->node_map[cur_border_index].pos,  Path->node_map[from_index].pos) * starting_prior);
        if(!IsIndexInArray(open, cur_border_index) or priority <= cost_so_far){
          Path->node_map[cur_border_index].parent_index = current_index;
          //Path->priority_list[current_index] = priority;
          cost_so_far += priority;
          //cost_so_far = Path->priority_list[cur_border_index];
          if(!IsIndexInArray(open, cur_border_index)){
            ArrayPushInt(open, cur_border_index);
          }
        }
      }
    }
  }
}*/




int main(){
  InitWindow(screenWidth, screenHeight, "My Game");
  SetTargetFPS(_TARGET_FPS);
  InitArrayInstance(&inst_array, 16);
  InitArrayPtr(&g_pt_array, 1280);
  
  #if DEBUG_MODE
    
    printf("sizeof pt_array: %llu \n", sizeof(*g_pt_array.array) * g_pt_array.size);
    printf("sizeof inst array: %llu \n", sizeof(*inst_array.array )* inst_array.size);
  #endif
  CellGrid2D main_grid = CreateCellGrid2D(WorldGridWidth, WorldGridHeight);
  
  GridVector2D grid_on_hover_pos = {0,0};
  #pragma region Initialaze Camera
  camera.zoom = 2.0f;
  camera.offset = (Vector2){ screenWidth/2, screenHeight/2};
  camera.target = (Vector2) {0, 0};
  camera.rotation = 0.0f;
  CameraInstance2D CurrentCamera = {
    .target_instance = NULL,
    .target_pos = {0,0},
    .camera = &camera
  };
 
  #pragma endregion
  #pragma region Load sprites
  Texture2D player_animation_sprite = LoadTexture("sprites/player32.png");
  Texture2D dude_animation_sprite = LoadTexture("sprites/test32.png");
  Texture2D grass_tile = LoadTexture("sprites/grass_tile.png");
  Texture2D rock_tile = LoadTexture("sprites/rock_tile.png");
  Texture2D selected_tile = LoadTexture("sprites/grid_selected.png");
  Texture2D solder_sprite = LoadTexture("sprites/solder.png");
  Texture2D red_tile = LoadTexture("sprites/red_tile.png");
  Texture2D blue_tile = LoadTexture("sprites/blue_tile.png");
  Animation2D player_animation = CreateAnimation2D(&player_animation_sprite, 1, _LOW_SPEED_ANIMATION);
  Animation2D solder_animation = CreateAnimation2D(&solder_sprite, 1, _LOW_SPEED_ANIMATION);
  Animation2D dude_animation = CreateAnimation2D(&dude_animation_sprite, 6, _HIGHT_SPEED_ANIMATION-10);
  Animation2D grass_animation = CreateAnimation2D(&grass_tile, 1, _LOW_SPEED_ANIMATION);
  Animation2D rock_animation = CreateAnimation2D(&rock_tile, 1, _LOW_SPEED_ANIMATION);
  Animation2D red_tile_animation = CreateAnimation2D(&red_tile, 1, _LOW_SPEED_ANIMATION);
  Animation2D blue_tile_animation = CreateAnimation2D(&blue_tile, 1, _LOW_SPEED_ANIMATION);

  Animation2D empty_animation;
  #pragma endregion
  #pragma region Create Instance
  
  
  Terrain Terrain_Grass = {
    .type = LAND,
    .move_cost = 4,
  };
  Terrain Terrain_Rocks = {
    .type = LAND,
    .move_cost = 64,
  };
  
  /*main_grid.grid[4][4].exist = FALSE;
   main_grid.grid[4][5].exist = FALSE;
   main_grid.grid[4][6].exist = FALSE;
   main_grid.grid[5][4].exist = FALSE;
   //main_grid.grid[5][7].exist = FALSE;
   main_grid.grid[5][6].exist = FALSE;
   main_grid.grid[6][6].exist = FALSE;
   main_grid.grid[6][4].exist = FALSE;
   main_grid.grid[6][5].exist = FALSE;*/
  
  #pragma endregion
  for(u32 i = 0;i<main_grid.height;i++){
    for(u32 ii = 0;ii<main_grid.width;ii++){
      if(!GetRandomValue(0,5)){
        main_grid.grid[i][ii].animation = rock_animation;
        main_grid.grid[i][ii].nature.terrain = &Terrain_Rocks;
      } else {
        main_grid.grid[i][ii].animation = grass_animation;
        main_grid.grid[i][ii].nature.terrain = &Terrain_Grass;
      }
    }
  }
  int number = 0;
  
  printf("assign complete \n");
  GLOBAL_PTR_ARRAY[G_SCREEN_W] = SetCustomPointer((int*)&screenWidth, PT_INT);
  GLOBAL_PTR_ARRAY[G_SCREEN_H] = SetCustomPointer((int*)&screenHeight, PT_INT);
  GLOBAL_PTR_ARRAY[G_WORLDGRID_H] = SetCustomPointer((unsigned int*)&WorldGridHeight, PT_UINT);
  GLOBAL_PTR_ARRAY[G_WORLDGRID_W] = SetCustomPointer((unsigned int*)&WorldGridWidth, PT_UINT);

  GLOBAL_PTR_ARRAY[G_CURCELL] = SetCustomPointer((Cell*)&cell_on_hover, PT_CELL);
  GLOBAL_PTR_ARRAY[G_LOCK_ON_CELL] = SetCustomPointer((Cell*)&lock_on_cell, PT_CELL);
  GLOBAL_PTR_ARRAY[G_EMPTY_CELL] = SetCustomPointer((Cell*)&empty_lockon_cell, PT_CELL);
  GLOBAL_PTR_ARRAY[G_MAIN_GRID] = SetCustomPointer((CellGrid2D*)&main_grid, PT_CELL_GRID2D);

  GLOBAL_PTR_ARRAY[G_MOUSE_WORLD_POS] = SetCustomPointer((Vector2*)&mouse_world_pos, PT_VECTOR2);
  GLOBAL_PTR_ARRAY[G_INSTARRAY] = SetCustomPointer((InstanceArray*)&inst_array, PT_INST_ARRAY);
  GLOBAL_PTR_ARRAY[G_WORLDCAM] = SetCustomPointer((CameraInstance2D*)&CurrentCamera, PT_CAMERA);

  GLOBAL_LOCKON_CELL = GLOBAL_PTR_ARRAY[G_EMPTY_CELL].p_cell;
  NewInstance(&g_pt_array,(Vector2){0,0}, &inst_array, &solder_animation, SOLDER);
  ASPath path;
  CreatePath(&path, &main_grid);
  /*CreateASNode(&main_grid, &path.node_map);
  InitArrayInt(&path.open, (size_t)(sizeof(int ) * (main_grid.width *main_grid.height)));
  InitArrayInt(&path.closed, (size_t)(sizeof(int ) * (main_grid.width *main_grid.height)));
  InitArrayInt(&path.final_path, (size_t)(sizeof(int ) * (main_grid.width *main_grid.height)));
  path.priority_list = (int *)malloc(sizeof(int) * (main_grid.width *main_grid.height));
  path.max_h = main_grid.height;
  path.max_w = main_grid.width;
  */
  for(int i = 0;i< (path.max_h * path.max_w)-1;i++){
    path.priority_list[i] = 0;
  }
  while (!WindowShouldClose()) {
    #pragma region Step Invent
    //inst_array.array[0].f_create(&inst_array.array[0], GLOBAL_PTR_ARRAY);
    mouse_world_pos = GetScreenToWorld2D(GetMousePosition(), camera);
    number = 0;
    if(IsKeyPressed(KEY_T)){
      NewInstance(&g_pt_array,(Vector2){0,0}, &inst_array, &solder_animation, SOLDER);
    }
    #pragma region camera ivent
    //camera.target = player.pos;
    #pragma endregion
    for(unsigned int i = 0;i < inst_array.used;i++){
      if(inst_array.array[i].exist){
        number++;
      }
    }; 
    prev_on_hover = cell_on_hover;
    cell_on_hover = GetGridOnHover(mouse_world_pos, &grid_on_hover_pos, &main_grid, (GridVector2D){.x = main_grid.width, .y =main_grid.height}, &cell_on_hover);
    
    if( GLOBAL_LOCKON_CELL != &empty_lockon_cell){
      if(prev_on_hover.ID != cell_on_hover.ID){
        freeUsedAInt(&path.open);
        freeUsedAInt(&path.closed);
        freeUsedAInt(&path.final_path);
        FindPathDi(&path, GLOBAL_LOCKON_CELL->grid_pos, cell_on_hover.grid_pos);
        //Astar(&path, GLOBAL_LOCKON_CELL->grid_pos, cell_on_hover.grid_pos);
      }
      //printf("open used: %llu\n", path.open.used );
      for(u32 i = 0;i < path.open.used;i++){
        //printf("open val: %d\n", path.open.array[i] );
        u32 _x = path.node_map[path.open.array[i]].pos.x;
        u32 _y = path.node_map[path.open.array[i]].pos.y;
        //printf("x:%u y: %u\n", _x,_y );
        main_grid.grid[_y][_x].animation.color = BROWN;
      }
      for(u32 i = 0;i < path.closed.used;i++){
        u32 _x = path.node_map[path.closed.array[i]].pos.x;
        u32 _y = path.node_map[path.closed.array[i]].pos.y;
        main_grid.grid[_y][_x].animation.color = RED;
      }
      for(u32 i = 0;i < path.final_path.used;i++){
        u32 _x = path.node_map[path.final_path.array[i]].pos.x;
        u32 _y = path.node_map[path.final_path.array[i]].pos.y;
        main_grid.grid[_y][_x].animation.color = BLUE;
      }
      
    } else {
      if(path.closed.used > 0 || path.open.used > 0 || path.final_path.used > 0){
        freeUsedAInt(&path.open);
        freeUsedAInt(&path.closed);
        freeUsedAInt(&path.final_path);
      }
    }
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) ){
      if(GLOBAL_LOCKON_CELL == &empty_lockon_cell){
        GLOBAL_LOCKON_CELL = &(MAIN_GRID_CUR_POS); 
      } else {
        #if DEBUG_MODE
          printf("%p : %p \n", GLOBAL_LOCKON_CELL, &(MAIN_GRID_CUR_POS));
        #endif
        if(GLOBAL_LOCKON_CELL == &(MAIN_GRID_CUR_POS)){
          #if DEBUG_MODE
            printf("lock on empty cell\n");
          #endif
          GLOBAL_LOCKON_CELL = &empty_lockon_cell;
        } else {
          #if DEBUG_MODE
            printf("%p \n", &(MAIN_GRID_CUR_POS));
          #endif
          GLOBAL_LOCKON_CELL = &(MAIN_GRID_CUR_POS);
        }
      }
    }
    if(IsKeyDown(KEY_MINUS) && GLOBAL_CURRENT_CAMERA->zoom > MIN_ZOOM ){
      GLOBAL_CURRENT_CAMERA->zoom -= 0.05F;
    }else if(IsKeyDown(KEY_EQUAL) && GLOBAL_CURRENT_CAMERA->zoom < MAX_ZOOM){
      GLOBAL_CURRENT_CAMERA->zoom += 0.05F;
    }
    #pragma endregion
    
    UpdateInstances(&inst_array, GLOBAL_PTR_ARRAY);
    
    #pragma region Draw event
    BeginDrawing();
      ClearBackground(GRAY);
      BeginMode2D(*GLOBAL_CURRENT_CAMERA);
        
        UpdateDrawCells(&main_grid);
        for(unsigned int i = 0;i <= main_grid.height;i++){
          DrawLine(0,PIXEL_SIZE * i,PIXEL_SIZE * main_grid.width ,PIXEL_SIZE * i , BLACK);
        }
        for(unsigned int i = 0;i <= main_grid.width;i++){
          DrawLine(PIXEL_SIZE * i,0,  PIXEL_SIZE * i,PIXEL_SIZE * main_grid.height , BLACK);
        }
        #if DEBUG_MODE
        for(unsigned int h = 0;h < path.max_h ;h++){
          for(unsigned int w = 0;w <path.max_w;w++){
            DrawText(TextFormat("G:%i",path.node_map[w + (h * path.max_w)].G), w * PIXEL_SIZE +2 , h * PIXEL_SIZE+ 12, 12, WHITE);
            DrawText(TextFormat("H:%i",path.node_map[w + (h * path.max_w)].H), w * PIXEL_SIZE +2,  h * PIXEL_SIZE, 12, WHITE);
          }
        }
        #endif
        //DrawTexture(selected_tile, (grid_on_hover_pos.x * PIXEL_SIZE)-1, (grid_on_hover_pos.y * PIXEL_SIZE)-1, WHITE);
        //DrawRectangleLines( (grid_on_hover_pos.x * PIXEL_SIZE)-1, (grid_on_hover_pos.y * PIXEL_SIZE)-1,PIXEL_SIZE+2, PIXEL_SIZE+2, YELLOW);
        UpdateDrawInstances(&inst_array, GLOBAL_PTR_ARRAY);
        DrawRectangleLines( (cell_on_hover.grid_pos.x * PIXEL_SIZE), (cell_on_hover.grid_pos.y * PIXEL_SIZE),PIXEL_SIZE, PIXEL_SIZE, WHITE);
        if(GLOBAL_LOCKON_CELL != &empty_lockon_cell){
          DrawRectangleLines( (GLOBAL_LOCKON_CELL->grid_pos.x * PIXEL_SIZE), (GLOBAL_LOCKON_CELL->grid_pos.y * PIXEL_SIZE),PIXEL_SIZE, PIXEL_SIZE, YELLOW);
        }
        DrawText(TextFormat("X: %i",grid_on_hover_pos.x), mouse_world_pos.x, mouse_world_pos.y,16 ,BLACK);
        DrawText(TextFormat("Y: %i",grid_on_hover_pos.y), mouse_world_pos.x, mouse_world_pos.y+16, 16,BLACK);
        
        

      EndMode2D();
      UpdateDrawGUIInstances(&inst_array, GLOBAL_PTR_ARRAY);
      DrawText(TextFormat("%i",number), 4,4,24,BLACK);
      DrawText(TextFormat("%g",mouse_world_pos.x), 4,4+24,24,BLACK);
      DrawText(TextFormat("%g",mouse_world_pos.y), 4,4+48,24,BLACK);
    EndDrawing();
    #pragma endregion
    #pragma region Camera Update Ivent
      //CurrentCamera.target_instance = inst_array.array[2];
      if(CurrentCamera.target_instance != NULL && CurrentCamera.target_instance->exist){
        CurrentCamera.camera->target = CurrentCamera.target_instance->pos;
      } else {
        if(IsKeyDown(KEY_UP)){
          CurrentCamera.target_pos.y -= 2;
        }
        if(IsKeyDown(KEY_DOWN)){
          CurrentCamera.target_pos.y += 2;
        }
        if(IsKeyDown(KEY_LEFT)){
          CurrentCamera.target_pos.x -= 2;
        }
        if(IsKeyDown(KEY_RIGHT)){
          CurrentCamera.target_pos.x  += 2;
        }
        CurrentCamera.camera->target = CurrentCamera.target_pos;
      }
    #pragma endregion
  }
  UnloadTexture(dude_animation_sprite);
  UnloadTexture(player_animation_sprite);
  UnloadTexture(grass_tile);
  CloseWindow();
  return 0;
}
