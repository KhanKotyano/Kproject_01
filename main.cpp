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
//Var my_int ;
IntArray BigA;


Vector2 mouse_world_pos;
const int screenWidth = 1280;
const int screenHeight = 720;
Camera2D camera = { 0 };
Camera3D camera_3d = { 0 };
InstanceArray inst_array;

//Instance *test_inst_array[_MAX_INSTANCES] ;
//int _a = sizeof(inst_array);

int main(){
  
  InitWindow(screenWidth, screenHeight, "My Game");
  SetTargetFPS(_TARGET_FPS);
  #pragma region Initialaze Camera
  camera.zoom = 2.0f;
  camera.offset = (Vector2){ screenWidth/2, screenHeight/2};
  camera.target = (Vector2) {0, 0};
  camera.rotation = 0.0f;


  camera_3d.position = (Vector3){ 10.0f, 10.0f, 8.0f };
  camera_3d.target = (Vector3){ 0.0f, 0.0f, 0.0f };
  camera_3d.up = (Vector3){ 0.0f, 1.0f, 0.0f };
  camera_3d.fovy = 60.0f;
  camera_3d.projection = CAMERA_PERSPECTIVE;
  #pragma endregion
  #pragma region Load sprites
  Texture2D enemy_sprite = LoadTexture("sprites/red_box.png");
  Texture2D player_animation_sprite = LoadTexture("sprites/player32.png");
  Texture2D dude_animation_sprite = LoadTexture("sprites/test32.png");
  #pragma endregion
  #pragma region Create Instance
  Animation2D player_animation = CreateAnimation2D(&player_animation_sprite, 6, _LOW_SPEED_ANIMATION);
  Animation2D dude_animation = CreateAnimation2D(&dude_animation_sprite, 6, _HIGHT_SPEED_ANIMATION-10);
  //void(*array[])(Instance*) = {&PlayerIvent};
  Instance player = CreateInstanceType(Vector2{0,0}, &player_animation_sprite, &player_animation, TYPE::PLAYER);
  #pragma endregion
  int number = 0;
  InitArrayInstance(&inst_array, 16);

  /*
  InitArrayInt(&BigA, 10);
  for(int i = 0;i< 10;i++){
    ArrayPushInt(&BigA, i+12);
  }
  for(int i = 0;i< 10;i++){
    printf(IntToString(i));
    printf(":");
    printf(IntToString(BigA.array[i]));
    printf("\n");
  }
  printf("used space:");
  printf(IntToString((int)BigA.used));
  printf("\n");
  //BigA.array[1] = NULL;
  //BigA.array[0] = _EMPTY;
  //BigA.array[3] = _EMPTY;
  //BigA.array[9] = _EMPTY;
  bool cool = RedoIntArray(&BigA);
  printf("%s", cool ? "true" : "false");
  printf("\n");
  for(int i = 0;i< 10;i++){
    printf(IntToString(i));
    printf(":");
    printf(IntToString(BigA.array[i]));
    printf("\n");
  }
  printf("used space:");
  printf(IntToString((int)BigA.used));
  printf("\n");

  printf("Size of array: ");
  printf(IntToString( BigA.size));
  printf("\n");
  
  freeArrayInt(&BigA);
  
  printf("Size of freearray: ");
  printf(IntToString( BigA.used));
  printf("\n");
  
  printf("Size of main array: ");
  printf(IntToString(_a));
  printf("\n");
  */
  
  //player.function = &PlayerIvent;

  while (!WindowShouldClose()) {
    #pragma region Step Invent
    mouse_world_pos = GetScreenToWorld2D(GetMousePosition(), camera);
    number = 0;
    if(IsKeyPressed(KEY_R)){
      AddInstanceType(mouse_world_pos, &inst_array, &enemy_sprite, &dude_animation, TYPE::ENEMY);
    }
    if(IsKeyPressed(KEY_T)){
      int rd = GetRandomValue(0, inst_array.used-1);
      inst_array.array[rd] = {0};
     //AddInstancePointer(&dude, test_inst_array, mouse_world_pos);
    }
    //PlayerIvent(&player);
    player.f_array[0](&player);
    UpdateInstances(&inst_array);
    #pragma region camera ivent
    camera.target = player.pos;
    #pragma endregion
    for(unsigned int i = 0;i < inst_array.used;i++){
      if(inst_array.array[i].exist){
        number++;
      }
    }; 
    #pragma endregion
    #pragma region Draw event
    BeginDrawing();
      ClearBackground(RAYWHITE);
      BeginMode2D(camera);
        //UpdateAnimateInstances(&inst_array);
        UpdateDrawInstances(&inst_array);
        player.f_draw_array[0](&player);
        //DrawAndAnimate(&player);
        DrawText(TextFormat("%g",player.pos.y), player.pos.x, player.pos.y - 8, 8, BLACK);
        DrawText(TextFormat("%g",player.pos.x), player.pos.x , player.pos.y- 16, 8, BLACK);

        
      EndMode2D();
      DrawText(TextFormat("%i", player.animation.curretnt_frame), 40,4,24,RED);
      DrawText(TextFormat("%i",number), 4,4,24,BLACK);
      
    EndDrawing();

    #pragma endregion
  }
  CloseWindow();
  return 0;
}
