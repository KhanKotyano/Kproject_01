//#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "rlib/raylib.h"
#include "rlib/raymath.h"
#include "rlib/rlgl.h"

#include "functions/functions.h"



Vector2 mouse_world_pos;
const int screenWidth = 1280;
const int screenHeight = 720;
static Camera2D camera = { 0 };
//Camera3D camera_3d = { 0 };
static InstanceArray inst_array;

//Instance *test_inst_array[_MAX_INSTANCES] ;
//int _a = sizeof(inst_array);

int main(){
  InitWindow(screenWidth, screenHeight, "My Game");
  SetTargetFPS(_TARGET_FPS);
  InitArrayInstance(&inst_array, 16);
  #pragma region Initialaze Camera
  camera.zoom = 2.0f;
  camera.offset = (Vector2){ screenWidth/2, screenHeight/2};
  camera.target = (Vector2) {0, 0};
  camera.rotation = 0.0f;
  CameraInstance2D CurrentCamera = {
    .camera = &camera
  };

  #pragma endregion
  #pragma region Load sprites
  Texture2D player_animation_sprite = LoadTexture("sprites/player32.png");
  Texture2D dude_animation_sprite = LoadTexture("sprites/test32.png");
  #pragma endregion
  #pragma region Create Instance
  
  Animation2D player_animation = CreateAnimation2D(&player_animation_sprite, 6, _LOW_SPEED_ANIMATION);
  Animation2D dude_animation = CreateAnimation2D(&dude_animation_sprite, 6, _HIGHT_SPEED_ANIMATION-10);

  Animation2D empty_animation;
  AddInstanceType((Vector2){0,0}, &inst_array, &empty_animation, NOTHING);
  
  AddInstanceType((Vector2){0,0}, &inst_array, &player_animation, PLAYER);
  AddInstanceType((Vector2){16,16}, &inst_array,  &dude_animation, ENEMY);
  AddInstanceType((Vector2){32,32}, &inst_array,  &dude_animation, ENEMY);
  AddInstanceType((Vector2){64,64}, &inst_array,  &dude_animation, ENEMY);
  AddInstanceType((Vector2){100,100}, &inst_array,  &dude_animation, ENEMY);
  AddInstanceType((Vector2){26,27}, &inst_array,  &dude_animation, ENEMY);
  #pragma endregion
  int number = 0;
  CellGrid2D test_grid = CreateCellGrid2D(10, 10);
  
  while (!WindowShouldClose()) {
    #pragma region Step Invent
    mouse_world_pos = GetScreenToWorld2D(GetMousePosition(), camera);
    number = 0;
    if(IsKeyPressed(KEY_R)){
      AddInstanceType(mouse_world_pos, &inst_array,  &dude_animation, ENEMY);
    }
    if(IsKeyPressed(KEY_T)){
      int rd = GetRandomValue(0, inst_array.used-1);
      inst_array.array[rd] = {0};
    }
    #pragma region camera ivent
    //camera.target = player.pos;
    #pragma endregion
    for(unsigned int i = 0;i < inst_array.used;i++){
      if(inst_array.array[i].exist){
        number++;
      }
    }; 
    #pragma endregion
    #pragma region Draw event
    UpdateInstances(&inst_array);
    BeginDrawing();
      ClearBackground(RAYWHITE);
      BeginMode2D(*CurrentCamera.camera);
        UpdateDrawInstances(&inst_array);
      EndMode2D();
      UpdateDrawGUIInstances(&inst_array);
      DrawText(TextFormat("%i",number), 4,4,24,BLACK);
    EndDrawing();
    #pragma endregion
    #pragma region Camera Update Ivent
      CurrentCamera.camera->target = inst_array.array[1].pos;
    #pragma endregion
  }
  CloseWindow();
  return 0;
}
