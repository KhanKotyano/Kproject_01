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
#include "functions/functions.h"






const int screenWidth = 1280;
const int screenHeight = 720;
unsigned int WorldGridHeight = 10;
unsigned int WorldGridWidth = 20;
Camera2D camera = { 0 };
//Camera3D camera_3d = { 0 };
InstanceArray inst_array;
IntArray creation_inst_array = { 0 };
//Instance **creation_inst_array; 
Cell cell_on_hover = { 0 }; 
Cell prev_on_hover = { 0 };
Cell lock_on_cell  = { 0 };
Cell empty_lockon_cell = { 0 };
Vector2 mouse_world_pos;
PointerArray g_pt_array;


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
  IntArray priority;
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
  //node_str->array;
  int return_val;
  
  unsigned int hight_index = 0;
  int prev_max_val = path_array[node_str->array[hight_index]].F;
  for(unsigned int i = 0;i < node_str->used;i++){
    if(path_array[node_str->array[i]].F < prev_max_val){
      hight_index = i;
    }
  }
  
  return_val = (int)(node_str->array[hight_index]);
  //printf("return val:%d", return_val);
  ArrayEmptyIndexInt(node_str, hight_index);
  //printf("after return val:%d", return_val);
  return return_val;
};
unsigned int GetMinValIndexArray(int *array, int *array2,unsigned int array_size){
  int return_val = INT_MIN;
  unsigned int min_index = 0;
  unsigned int i;
  for(i = 0;i<array_size;i++){
    if(array[array2[i]] < array[min_index]){min_index = i;}
  }
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
      (*ASNode_array)[cur_index].F = 0;//(int)(from_grid->grid[y][x].nature.terrain->move_cost);
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
int IsThisCloseGrid(GridVector2D a, GridVector2D b){
  return (int)(_abs64(a.x - b.x) + _abs64(a.y - b.y));
}
void AStar2(IntArray *open,IntArray *closed, GridVector2D max_pos, ASNode *path_array, GridVector2D from_node, GridVector2D target_node
            , IntArray *path_index){
  unsigned int max_index = max_pos.x * max_pos.y;
  unsigned int from_index = (from_node.x + (from_node.y * max_pos.x));
  unsigned int target_index = (target_node.x + (target_node.y * max_pos.x));
  if(path_array[target_index].can_move){
    ArrayPushInt(open, from_index );
    //ArrayPushInt(closed, from_index );
    int cur_border_index;
    #if DEBUG_MODE
      printf("START ASTAR \n");
    #endif
    int iteration = 0;
    int cost_so_far = 0;
    unsigned int current_index = 0;
    int *priority_list = (int*)malloc(sizeof(int) * (max_index));
    for(int i = 0; i < max_index;i++){
      priority_list[i] = path_array[i].F;
    }
    
    while(open->used){
      //printf("open used:%llu | open value %d\n", open->used, open->array[open->used-1]);
      iteration++;
      //printf("open used:%llu | open value %d\n", open->used, open->array[open->used-1]);
      current_index = GetMaxFCostIndex(open, path_array);//index2D of path_array
      //current_index = GetMinValIndexArray(priority_list, open->array,open->used);
      RedoIntArray(open);
      //printf("curr_index:%u\n", current_index); 
      //ArrayEmptyIndexInt(open, current_index);
      
      
      ArrayPushInt(closed, current_index);
      #if DEBUG_MODE
        printf("iteration:%d curr_index:%u\n", iteration, current_index);
      #endif
      if(current_index == target_index){
        #if DEBUG_MODE
          printf("path exist: cur_index:%u || target_index:%u \n", current_index, target_index);
        #endif
        
        while(current_index != from_index ){
          printf("current path index: %u\n", current_index);
          ArrayPushInt(path_index,current_index);
          current_index = path_array[current_index].parent_index;
        }
        printf("total path lenght: %llu\n", path_index->used);
        RedoIntArray(open); //Shift quque
        free(priority_list);
        //RedoIntArray(closed);
        return;
      }
      int priority = 0;
      for(int i = 0;i < path_array[current_index].border_nodes_size;i++){
        cur_border_index = path_array[current_index].border_nodes_index[i];
        if( IsIndexInArray(closed, cur_border_index) or !(path_array[cur_border_index].can_move) ){
          continue;
        } 
        priority = IsThisCloseGrid( path_array[cur_border_index].pos ,path_array[target_index].pos); 
        priority -= IsThisCloseGrid( path_array[cur_border_index].pos,  path_array[from_index].pos);
        priority_list[cur_border_index] = priority;
        if(!IsIndexInArray(open, cur_border_index) or priority_list[cur_border_index] >= priority_list[current_index]){
          path_array[cur_border_index].parent_index = current_index;
          if(!IsIndexInArray(open, cur_border_index)){
            ArrayPushInt(open, cur_border_index);
          }
        }
      }
      //printf("open size:%llu \n",open->used);
      //RedoIntArray(open);
    }
    free(priority_list);
  }
}



int main(){
  InitWindow(screenWidth, screenHeight, "My Game");
  SetTargetFPS(_TARGET_FPS);
  InitArrayInstance(&inst_array, 16);
  InitArrayPtr(&g_pt_array, 1280);
  //InitArray(&inst_array, 16);
  //InitArrayPtr()
  //ASPathCreate(&path_source, NULL, &(GridVector2D){1,1}, &(GridVector2D){10,10});
  
  #if DEBUG_MODE
    
    printf("sizeof pt_array: %llu \n", sizeof(*g_pt_array.array) * g_pt_array.size);
    printf("sizeof inst array: %llu \n", sizeof(*inst_array.array )* inst_array.size);
    /*IntArray array; 
    InitArrayInt(&array, 32);
    for(int i = 0; i< array.size; i++){
      array.array[i] = i;
    }
    EmptyIntArray(&array, 0);
    RedoIntArray(&array);
    for(int i = 0; i< array.used; i++){
      printf("array[%d]: %d \n", i, array.array[i]);
    }
    printf("array used: %d", array.used);
    freeArrayInt(&array);*/
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
  Texture2D selected_tile = LoadTexture("sprites/grid_selected.png");
  Texture2D solder_sprite = LoadTexture("sprites/solder.png");
  Texture2D red_tile = LoadTexture("sprites/red_tile.png");
  Texture2D blue_tile = LoadTexture("sprites/blue_tile.png");
  #pragma endregion
  #pragma region Create Instance
  
  Animation2D player_animation = CreateAnimation2D(&player_animation_sprite, 1, _LOW_SPEED_ANIMATION);
  Animation2D solder_animation = CreateAnimation2D(&solder_sprite, 1, _LOW_SPEED_ANIMATION);
  Animation2D dude_animation = CreateAnimation2D(&dude_animation_sprite, 6, _HIGHT_SPEED_ANIMATION-10);
  Animation2D grass_animation = CreateAnimation2D(&grass_tile, 1, _LOW_SPEED_ANIMATION);
  Animation2D red_tile_animation = CreateAnimation2D(&red_tile, 1, _LOW_SPEED_ANIMATION);
  Animation2D blue_tile_animation = CreateAnimation2D(&blue_tile, 1, _LOW_SPEED_ANIMATION);

  Animation2D empty_animation;
  Terrain Terrain_Grass = {
    .type = LAND,
    .move_cost = 10
  };
  for(u32 i = 0;i<main_grid.height;i++){
    for(u32 ii = 0;ii<main_grid.width;ii++){
      main_grid.grid[i][ii].animation = grass_animation;
      //main_grid.grid[i][ii].animation = grass_animation;
      main_grid.grid[i][ii].nature.terrain = &Terrain_Grass;
    }
  }
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
  CreateASNode(&main_grid, &path.node_map);
  InitArrayInt(&path.open, (size_t)(sizeof(int ) * (main_grid.width *main_grid.height)));
  InitArrayInt(&path.closed, (size_t)(sizeof(int ) * (main_grid.width *main_grid.height)));
  InitArrayInt(&path.final_path, (size_t)(sizeof(int ) * (main_grid.width *main_grid.height)));
  #if DEBUG_MODE
    //pathfinding_govna
    //CreateASNode(&main_grid, &path.node_map);
    //InitArrayInt(&path.open, (size_t)(sizeof(int ) * (main_grid.width *main_grid.height)));
    //InitArrayInt(&path.closed, (size_t)(sizeof(int ) * (main_grid.width *main_grid.height)));
    //InitArrayInt(&path.final_path, (size_t)(sizeof(int ) * (main_grid.width *main_grid.height)));
    /*AStar2(&path.open, &path.closed, (GridVector2D){.x = main_grid.width ,.y =main_grid.height },path.node_map
    , (GridVector2D){0,0}, (GridVector2D){5,5}
    , &path.final_path);*/
    //printf("open used: %llu \n", path.open.used);
  #endif
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
        AStar2(&path.open, &path.closed, (GridVector2D){.x = main_grid.width ,.y =main_grid.height }
              ,path.node_map
              ,GLOBAL_LOCKON_CELL->grid_pos, cell_on_hover.grid_pos
              ,&path.final_path);
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
