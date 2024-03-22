//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
#include <time.h>

#include "rlib/raylib.h"
#include "rlib/raymath.h"
#include "rlib/rlgl.h"

#include "functions/functions.h"
//#include "functions/f_common.c"
//#include "functions/f_stack.c"
//#include "functions/f_instance.c"

#define _NEAR_BLACK (Color){15, 15, 15, 255}

const int screenWidth = 1280;
const int screenHeight = 720;
Camera2D camera = { 0 };
Camera3D camera_3d = { 0 };

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
  Instance player = CreateInstance(Vector2{0,0}, &player_sprite);
  #pragma endregion
  UnloadTexture(player_sprite);
  player_sprite = LoadTexture("sprites/red_box.png");
  
  while (!WindowShouldClose()) {
    #pragma region Step Invent
    //UpdateStepIvent();
    PlayerIvent(player);
    camera.target = player.pos;
    #pragma endregion
    #pragma region Draw event
    BeginDrawing();
      ClearBackground(RAYWHITE);
      BeginMode2D(camera);
        char *player_posx = FloatToString(player.pos.y);
        char *player_posy = FloatToString(player.pos.x);
        
        DrawTextureEx(*player.sprite, Vector2 {0,0}, 0, 1, GREEN);
        DrawTextureEx(*player.sprite, player.pos, player.angle, player.scale, WHITE);
        DrawText(player_posx, player.pos.x, player.pos.y, 8, BLACK);
        DrawText(player_posy, player.pos.x , player.pos.y+ 24, 8, BLACK);
        

        free(player_posx);
        free(player_posy);
      EndMode2D();
      
    EndDrawing();

    #pragma endregion
  }
  CloseWindow();
  return 0;
}
