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
Cell lock_on_cell  = { 0 };
Cell empty_lockon_cell = { 0 };
Vector2 mouse_world_pos;
PointerArray g_pt_array;
//custom_pointer global_pointer_array[1280];

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



int main(){
  InitWindow(screenWidth, screenHeight, "My Game");
  SetTargetFPS(_TARGET_FPS);
  InitArrayInstance(&inst_array, 16);
  InitArrayPtr(&g_pt_array, 1280);
  //InitArray(&inst_array, 16);
  //InitArrayPtr()

  #if DEBUG_MODE
    //printf("%d \n", (int)sizeof(global_pointer_array));
    //printf("%d \n", (int)sizeof(inst_array.array));
  #endif
  CellGrid2D main_grid = CreateCellGrid2D(WorldGridWidth, WorldGridHeight);
  
  GridVector2D grid_on_hover_pos = {0,0};
  #pragma region Initialaze Camera
  camera.zoom = 2.0f;
  camera.offset = (Vector2){ screenWidth/2, screenHeight/2};
  camera.target = (Vector2) {0, 0};
  camera.rotation = 0.0f;
  CameraInstance2D CurrentCamera = {
    .target_instance = nullptr,
    .target_pos = {0,0},
    .camera = &camera
  };
 
  #pragma endregion
  #pragma region Load sprites
  Texture2D player_animation_sprite = LoadTexture("sprites/player32.png");
  Texture2D dude_animation_sprite = LoadTexture("sprites/test32.png");
  Texture2D grass_tile = LoadTexture("sprites/grass_tile_grid.png");
  Texture2D selected_tile = LoadTexture("sprites/grid_selected.png");
  #pragma endregion
  #pragma region Create Instance
  
  Animation2D player_animation = CreateAnimation2D(&player_animation_sprite, 6, _LOW_SPEED_ANIMATION);
  Animation2D dude_animation = CreateAnimation2D(&dude_animation_sprite, 6, _HIGHT_SPEED_ANIMATION-10);

  Animation2D empty_animation;
  for(u32 i = 0;i<main_grid.height;i++){
    for(u32 ii = 0;ii<main_grid.width;ii++){
      main_grid.grid[i][ii].static_sprite = &grass_tile;
    }
  }
   main_grid.grid[4][4].exist = FALSE;
   main_grid.grid[4][5].exist = FALSE;
   main_grid.grid[4][6].exist = FALSE;
   main_grid.grid[5][4].exist = FALSE;
   //main_grid.grid[5][7].exist = FALSE;
   main_grid.grid[5][6].exist = FALSE;
   main_grid.grid[6][6].exist = FALSE;
   main_grid.grid[6][4].exist = FALSE;
   main_grid.grid[6][5].exist = FALSE;
  
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
  NewInstance(&g_pt_array,(Vector2){0,0}, &inst_array, &player_animation, PLAYER);
  while (!WindowShouldClose()) {
    #pragma region Step Invent
    //inst_array.array[0].f_create(&inst_array.array[0], GLOBAL_PTR_ARRAY);
    mouse_world_pos = GetScreenToWorld2D(GetMousePosition(), camera);
    number = 0;
    if(IsKeyPressed(KEY_T)){
      NewInstance(&g_pt_array,(Vector2){0,0}, &inst_array, &player_animation, PLAYER);
    }
    #pragma region camera ivent
    //camera.target = player.pos;
    #pragma endregion
    for(unsigned int i = 0;i < inst_array.used;i++){
      if(inst_array.array[i].exist){
        number++;
      }
    }; 
    cell_on_hover = GetGridOnHover(mouse_world_pos, &grid_on_hover_pos, &main_grid, (GridVector2D){WorldGridWidth,WorldGridHeight}, &cell_on_hover);
    if(IsKeyPressed(KEY_R)){
      NewInstance(&g_pt_array,*GLOBAL_PTR_ARRAY[G_MOUSE_WORLD_POS].p_vector2D, &inst_array,  &dude_animation, ENEMY);
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
      if(CurrentCamera.target_instance != nullptr && CurrentCamera.target_instance->exist){
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
