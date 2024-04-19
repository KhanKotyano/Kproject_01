#include "functions.h"
void PlayerMainDraw(Instance *self, custom_pointer *global_pointer_array){
  DrawAndAnimate(self);
  DrawText(TextFormat("%g",self->pos.y), self->pos.x, self->pos.y - 8, 8, BLACK);
  DrawText(TextFormat("%g",self->pos.x), self->pos.x , self->pos.y- 16, 8, BLACK);
};
void PlayerMainDrawGui(Instance *self, custom_pointer *global_pointer_array){
  DrawText(TextFormat("%g : %i",self->pos.y, global_pointer_array[G_CURCELL].p_cell->grid_pos.y),  6, 150, 24, BLACK);
  DrawText(TextFormat("%g : %i",self->pos.x, global_pointer_array[G_CURCELL].p_cell->grid_pos.y), 6, 100, 24, BLACK);
  DrawText(TextFormat("%i", self->animation.curretnt_frame), 40,4,24,RED);
}





void AssignDrawGUIFunction(void(**function)(Instance*, custom_pointer*), u16 _type){
  switch(_type){
    case PLAYER:{
      *function = &PlayerMainDrawGui;
      
    }break;
    case ENEMY:{
      *function = &DumpFunction;
      
    }break;
    default:{
      *function = &DumpFunction;
    }
  }
};
void AssignDrawFunction(void(**function)(Instance*, custom_pointer*), u16 _type){
  switch(_type){
    case PLAYER:{
      *function = &PlayerMainDraw;
      
    }break;
    case ENEMY:{
      *function = &DumpFunction;
      
    }break;
    default:{
      *function = &DumpFunction;
    }
  }
};