#include "functions.h"
void SolderMain(Instance *self, custom_pointer *global_pointer_array){
  if(self->state == SELECTED){
    if(global_pointer_array[G_LOCK_ON_CELL].p_cell != self->custom_var.my_cell  
    && global_pointer_array[G_LOCK_ON_CELL].p_cell != global_pointer_array[G_EMPTY_CELL].p_cell){
      //self->state = NOT_SELECTED;
      self->custom_var.my_cell = global_pointer_array[G_LOCK_ON_CELL].p_cell;
    }
  }
  self->pos.x = (float)(self->custom_var.my_cell->grid_pos.x * PIXEL_SIZE);
  self->pos.y = (float)(self->custom_var.my_cell->grid_pos.y * PIXEL_SIZE);
  if(global_pointer_array[G_LOCK_ON_CELL].p_cell == self->custom_var.my_cell){
    self->state = SELECTED;
  } else {
    self->state = NOT_SELECTED;
  }
}
void SolderCreate(Instance *self, custom_pointer *global_pointer_array){
  //self->depth = GetRandomValue(1, 100);
  printf("SOLDER Created : %d\n", self->ID);
  self->exist = TRUE;
  self->state = INITIALIZED;
  self->custom_var.my_cell = &(global_pointer_array[G_MAIN_GRID].p_grid_cell2D->
    grid[global_pointer_array[G_CURCELL].p_cell->grid_pos.y][global_pointer_array[G_CURCELL].p_cell->grid_pos.x]);

  //global_pointer_array[G_MAIN_GRID].p_grid_cell2D->grid[GetRandomValue(0,10)][GetRandomValue(0,10)].exist = false;
};
void EnemyMainIvent(Instance *self, custom_pointer*){


};
void DumpFunction(Instance *self, custom_pointer*){return;};

void AssignFunction(void(**function)(Instance*, custom_pointer*), u16 _type){
  switch(_type){
    case SOLDER:{
      *function = &SolderMain;
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
    case SOLDER:{
      *function = &SolderCreate;
    }break;
    case ENEMY:{
      *function = &DumpFunction;
    }break;
    default:{
      *function = &DumpFunction;
    }break;
  }
  
};
