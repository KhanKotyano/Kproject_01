#include "functions.h"
void PlayerMain(Instance *self, custom_pointer *global_array){
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
    self->pos.x = (float)(global_array[G_CURCELL].p_cell->grid_pos.x * PIXEL_SIZE);
    self->pos.y = (float)(global_array[G_CURCELL].p_cell->grid_pos.y* PIXEL_SIZE);
    //self->pos = (Vector2){(float)(cell_on_hover->grid_pos.x * PIXEL_SIZE), (float)(cell_on_hover->grid_pos.y* PIXEL_SIZE)};
}
void EnemyMainIvent(Instance *self, custom_pointer*){


};
void DumpFunction(Instance *self, custom_pointer*){return;};

void AssignFunction(void(**function)(Instance*, custom_pointer*), u16 _type){
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
