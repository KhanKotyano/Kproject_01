//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
#include <time.h>

#include "rlib/raylib.h"
#include "rlib/raymath.h"
#include "rlib/rlgl.h"

#include "functions/functions.h"
//Var my_int ;



const int screenWidth = 1280;
const int screenHeight = 720;
Camera2D camera = { 0 };
Camera3D camera_3d = { 0 };
Instance inst_array[_MAX_INSTANCES] = {0};

int _a = sizeof(inst_array);
//Instance *_ip;
//int _b = sizeof(_ip);
//Instance _ib;
//int _c = sizeof(_ib);

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
  //Texture2D player_sprite = LoadTexture("sprites/idk.png");
  Texture2D player_animation_sprite = LoadTexture("sprites/test3.png");
  #pragma endregion
  #pragma region Create Instance
  Animation2D player_animation = CreateAnimation2D(&player_animation_sprite);
  Instance player = CreateInstance(Vector2{0,0}, &player_animation_sprite, &player_animation);
  #pragma endregion
  int number = 0;
  printf(IntToString(_a));
  printf("\n");
  //printf(IntToString(_b));
  //printf("\n");
  //printf(IntToString(_c));
  //printf("\n");
  while (!WindowShouldClose()) {
    #pragma region Step Invent
    number = 0;
    if(IsKeyPressed(KEY_R)){
      AddInstance(GetScreenToWorld2D(GetMousePosition(), camera), inst_array, &enemy_sprite, &player_animation);
    }
    PlayerIvent(player);
    UpdateInstances(inst_array);
    camera.target = player.pos;
    for(unsigned int i = 0;i<_MAX_INSTANCES;i++){
      if(inst_array[i].active){
        number++;
      }
    }; 
    
    #pragma endregion
    #pragma region Draw event
    BeginDrawing();
      ClearBackground(RAYWHITE);
      BeginMode2D(camera);
        //number++;
        
        UpdateDrawInstances(inst_array);

        char *player_posx = FloatToString(player.pos.y);
        char *player_posy = FloatToString(player.pos.x);
    
        //DrawTextureEx(*player.sprite, player.pos, player.angle, player.scale, GREEN);
        DrawAndAnimate(&player);
        DrawText(player_posx, player.pos.x, player.pos.y - 8, 8, BLACK);
        DrawText(player_posy, player.pos.x , player.pos.y- 16, 8, BLACK);

        free(player_posx);
        free(player_posy);
      EndMode2D();
      DrawText(IntToString(player.animation.curretnt_frame), 40,4,24,RED);
      DrawText(IntToString(number), 4,4,24,BLACK);
    EndDrawing();

    #pragma endregion
  }
  CloseWindow();
  return 0;
}
