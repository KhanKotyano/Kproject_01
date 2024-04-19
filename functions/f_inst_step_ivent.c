#include "functions.h"
void PlayerMain(Instance *self, custom_pointer *global_pointer_array){
    //self->depth = GetRandomValue(1, 100);
    if(global_pointer_array[G_LOCK_ON_CELL].p_cell != global_pointer_array[G_EMPTY_CELL].p_cell){
      self->pos.x = (float)(global_pointer_array[G_LOCK_ON_CELL].p_cell->grid_pos.x * PIXEL_SIZE);
      self->pos.y = (float)(global_pointer_array[G_LOCK_ON_CELL].p_cell->grid_pos.y* PIXEL_SIZE);
    }
    //self->pos = (Vector2){(float)(cell_on_hover->grid_pos.x * PIXEL_SIZE), (float)(cell_on_hover->grid_pos.y* PIXEL_SIZE)};
}
void PlayerCreate(Instance *self, custom_pointer *global_pointer_array){
    //self->depth = GetRandomValue(1, 100);
    printf("inside create ivent \n");
    self->custom_var.my_cell = global_pointer_array[G_LOCK_ON_CELL].p_cell;
    printf("end of create ivent\n");
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
void AssignCreateFunction(void(**function)(Instance*, custom_pointer*), u16 _type){
  switch(_type){
    case PLAYER:{
      *function = &PlayerCreate;
    }break;
    case ENEMY:{
      *function = &DumpFunction;
    }break;
    default:{
      *function = &DumpFunction;
    }break;
  }
  
};
