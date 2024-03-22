//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
#include <time.h>

#include "rlib/raylib.h"
#include "rlib/raymath.h"
#include "rlib/rlgl.h"

#include "functions/functions.h"



const int screenWidth = 1280;
const int screenHeight = 720;
Camera2D camera = { 0 };
Camera3D camera_3d = { 0 };
Instance inst_array[_MAX_INSTANCES] = {0};

int main(){
  InitWindow(screenWidth, screenHeight, "My Game");
  SetTargetFPS(60);
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
  Texture2D player_sprite = LoadTexture("sprites/idk.png");
  #pragma endregion
  #pragma region Create Object
  Instance player = CreateInstance(Vector2{0,0}, &player_sprite, inst_array);
  #pragma endregion
  //UnloadTexture(player_sprite);
  //player_sprite = LoadTexture("sprites/red_box.png");
  
  while (!WindowShouldClose()) {
    #pragma region Step Invent
    //PlayerIvent(player);
    UpdateInstances(inst_array);
    //PlayerIvent(player);
    camera.target = player.pos;
    #pragma endregion
    #pragma region Draw event
    BeginDrawing();
      ClearBackground(RAYWHITE);
      BeginMode2D(camera);
        UpdateDrawInstances(inst_array);
      EndMode2D();
    EndDrawing();

    #pragma endregion
  }
  CloseWindow();
  return 0;
}
