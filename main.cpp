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
  Texture2D enemy_sprite = LoadTexture("sprites/red_box.png");
  Texture2D player_sprite = LoadTexture("sprites/idk.png");
  #pragma endregion
  #pragma region Create Object
  Instance player = CreateInstance(Vector2{0,0}, &player_sprite);
  // AddInstance(Vector2{26,26}, inst_array, &enemy_sprite);
  #pragma endregion
  int number = 0;
  while (!WindowShouldClose()) {
    #pragma region Step Invent
    number = 0;
    if(IsKeyPressed(KEY_R)){
      AddInstance(GetScreenToWorld2D(GetMousePosition(), camera), inst_array, &enemy_sprite);
      TraceLog(LOG_INFO,IntToString(GetMousePosition().x));
      TraceLog(LOG_INFO,IntToString(GetMousePosition().x));
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
    
        DrawTextureEx(*player.sprite, player.pos, player.angle, player.scale, GREEN);
        DrawText(player_posx, player.pos.x, player.pos.y, 8, BLACK);
        DrawText(player_posy, player.pos.x , player.pos.y+ 24, 8, BLACK);
    
        free(player_posx);
        free(player_posy);
      EndMode2D();
      DrawText(IntToString(number), 0,0,24,BLACK);
    EndDrawing();

    #pragma endregion
  }
  CloseWindow();
  return 0;
}
