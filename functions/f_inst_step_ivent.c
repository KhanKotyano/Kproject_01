#include "functions.h"
void PlayerMain(Instance *self){
    //self->depth = GetRandomValue(1, 100);
    if(IsKeyDown(KEY_W)){
    self->pos.y -= 1;
    //self->scale -= 0.005f;
    }
    if(IsKeyDown(KEY_S)){
      self->pos.y += 1;
      //self->scale += 0.005f;
    }
    if(IsKeyDown(KEY_A)){
      self->pos.x -= 1;
    }
    if(IsKeyDown(KEY_D)){
      self->pos.x  += 1;
    }
    if (IsKeyDown(KEY_A)) self->angle--;
    else if (IsKeyDown(KEY_S)) self->angle++;
    //self->pos = (Vector2){(float)(cell_on_hover->grid_pos.x * PIXEL_SIZE), (float)(cell_on_hover->grid_pos.y* PIXEL_SIZE)};
}
void OtherPlayerMain(Instance *self, custom_pointer *global_array){
  //self->depth = GetRandomValue(1, 100);
  self->pos = {(float)(global_array[G_CURCELL].p_cell->grid_pos.x * PIXEL_SIZE), (float)(global_array[G_CURCELL].p_cell->grid_pos.y* PIXEL_SIZE)};
  //self->pos = {(float)GetRandomValue(0, 100), (float)GetRandomValue(0, 100)};
};
void EnemyMainIvent(Instance *self){


};
void DumpFunction(Instance *self){return;};

void AssignFunction(void(**function)(Instance*), u16 _type){
  switch(_type){
    case PLAYER:{
      *function = &PlayerMain;
    }break;
    case ENEMY:{
      *function = &DumpFunction;
    }break;
    default:{
      *function = &DumpFunction;
    }break;
  }
  
};
