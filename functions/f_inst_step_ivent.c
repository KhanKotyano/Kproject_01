#include "functions.h"
void PlayerMain(Instance *self){
    if(IsKeyDown(KEY_UP)){
    self->pos.y -= 1;
    //self->scale -= 0.005f;
    }
    if(IsKeyDown(KEY_DOWN)){
      self->pos.y += 1;
      //self->scale += 0.005f;
    }
    if(IsKeyDown(KEY_LEFT)){
      self->pos.x -= 1;
    }
    if(IsKeyDown(KEY_RIGHT)){
      self->pos.x  += 1;
    }
    if (IsKeyDown(KEY_A)) self->angle--;
    else if (IsKeyDown(KEY_S)) self->angle++;
}
void EnemyMainIvent(Instance *self){


}
void DumpFunction(Instance *self){return;};
